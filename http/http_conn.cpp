#include "http_conn.h"

#include <mysql/mysql.h>
#include <fstream>

//定义http响应的一些状态信息
const char *ok_200_title = "OK";
const char *error_400_title = "Bad Request";
const char *error_400_form = "Your request has bad syntax or is inherently impossible to staisfy.\n";
const char *error_403_title = "Forbidden";
const char *error_403_form = "You do not have permission to get file form this server.\n";
const char *error_404_title = "Not Found";
const char *error_404_form = "The requested file was not found on this server.\n";
const char *error_500_title = "Internal Error";
const char *error_500_form = "There was an unusual problem serving the request file.\n";

locker m_lock;
/*map:理解为一个字典类性,不过键值要提前指定好
map的实现不是哈希而是红黑树
初始化一个名字为hmap的map:  map<string,string> hmap; 
插入A:B的键值对:  hamp.insert(A,B); 
由键查值: hmap.find(A)
这里是类全局遍量,也就是说,它不是类中的遍量,而是类外部的变量.定义一次就可以.1
*/
map<string, string> users;
//http_conn类中的一个方法,传入参数为数据库连接池地址,没有返回值
void http_conn::initmysql_result(connection_pool *connPool)
{
    //先从连接池中取一个连接
    MYSQL *mysql = NULL;
    //从连接池中取一个已经建立好了的连接,对该连接获取用户名-密码表的资源
    //数据库连接的获与释放通过RAII机制封装,避免手动释放
    //这个函数只会被第一个http请求调用,后续http请求也可以获得mysql数据库连接
    //connectionRAII:从数据库连接池中取一个空闲链接存在&mysql中
    connectionRAII mysqlcon(&mysql, connPool);
    //在user表中检索username，passwd数据，浏览器端输入
    /*执行一个sql语句,添删查改的sql都可以.
    下面语句含义是,列出user table中username和passwd关键词中的全部内容
    (和用户输入比对判断是否是用户)*/
    if (mysql_query(mysql, "SELECT username,passwd FROM user"))
    {
        LOG_ERROR("SELECT error:%s\n", mysql_error(mysql));
    }

    //从表中检索完整的结果集
    //mysql_store_result:将结果集从mysql中取出,result指向一块内存
    MYSQL_RES *result = mysql_store_result(mysql);

    //下面两句话是冗余的,我查的就是username和passwd,必然就是这两列内容了.
    //返回结果集中的列数
    int num_fields = mysql_num_fields(result);
    //返回所有字段结构的数组
    MYSQL_FIELD *fields = mysql_fetch_fields(result);

    //从结果集中获取下一行，将对应的用户名和密码，存入map中

    while (MYSQL_ROW row = mysql_fetch_row(result))
    {
        string temp1(row[0]);
        string temp2(row[1]);
        /*此处users和webserver.cpp中的users定义完全不同
        此处users就是一个map(line 25),将一个字符串映射到另一个字符串(字典)
        webserver.cpp中的users只http请求队列
        */
        users[temp1] = temp2;
    }
}

//对文件描述符设置非阻塞
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
void addfd(int epollfd, int fd, bool one_shot, int TRIGMode)
{
    epoll_event event;
    event.data.fd = fd;

    if (1 == TRIGMode)
        event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    else
        event.events = EPOLLIN | EPOLLRDHUP;

    if (one_shot)
        event.events |= EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

//从内核时间表删除描述符
void removefd(int epollfd, int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

//将事件重置为EPOLLONESHOT
void modfd(int epollfd, int fd, int ev, int TRIGMode)
{
    epoll_event event;
    event.data.fd = fd;

    if (1 == TRIGMode)
        event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    else
        event.events = ev | EPOLLONESHOT | EPOLLRDHUP;

    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

int http_conn::m_user_count = 0;
int http_conn::m_epollfd = -1;

//关闭连接，关闭一个连接，客户总量减一
void http_conn::close_conn(bool real_close)
{
    if (real_close && (m_sockfd != -1))
    {
        printf("close %d\n", m_sockfd);
        removefd(m_epollfd, m_sockfd);
        m_sockfd = -1;
        m_user_count--;
    }
}

//初始化连接,外部调用初始化套接字地址
void http_conn::init(int sockfd, const sockaddr_in &addr, char *root, int TRIGMode,
                     int close_log, string user, string passwd, string sqlname)
{
    m_sockfd = sockfd;
    m_address = addr;

    addfd(m_epollfd, sockfd, true, m_TRIGMode);
    m_user_count++;

    //当浏览器出现连接重置时，可能是网站根目录出错或http响应格式出错或者访问的文件中内容完全为空
    doc_root = root;
    m_TRIGMode = TRIGMode;
    m_close_log = close_log;

    strcpy(sql_user, user.c_str());
    strcpy(sql_passwd, passwd.c_str());
    strcpy(sql_name, sqlname.c_str());

    init();
}

//初始化新接受的连接
//check_state默认为分析请求行状态
void http_conn::init()
{
    mysql = NULL;
    bytes_to_send = 0;
    bytes_have_send = 0;
    m_check_state = CHECK_STATE_REQUESTLINE;
    m_linger = false;
    m_method = GET;
    m_url = 0;
    m_version = 0;
    m_content_length = 0;
    m_host = 0;
    m_start_line = 0;
    m_checked_idx = 0;
    m_read_idx = 0;
    m_write_idx = 0;
    cgi = 0;
    m_state = 0;
    timer_flag = 0;
    improv = 0;

    memset(m_read_buf, '\0', READ_BUFFER_SIZE);
    memset(m_write_buf, '\0', WRITE_BUFFER_SIZE);
    memset(m_real_file, '\0', FILENAME_LEN);//把m_real_file制成长度为200的内部全是\0的字符数组
}

//从状态机，用于分析出一行内容
//返回值为行的读取状态，有LINE_OK,LINE_BAD,LINE_OPEN
//总结就是利用'\r''\n'代表换行的唯一性（有且只有这两个字符出现代表换行）来分割行
http_conn::LINE_STATUS http_conn::parse_line()
{
    char temp;
    /*m_checked_idx: 检查的字符的下标
    m_read_idx:读取的最后一个字符下标
    for循环意思是再读缓冲区中依次检查字符
    */
    for (; m_checked_idx < m_read_idx; ++m_checked_idx)
    {   //取当前字符
        temp = m_read_buf[m_checked_idx];
        if (temp == '\r')//请求只有\r\n同时出现表示换行,只出现其中一个均为错误,
        {   //如果下一个位置超过缓存区了,那属于读取不完整,返回LINE_OPEN
            if ((m_checked_idx + 1) == m_read_idx)
                return LINE_OPEN;
            /*如果下一个是\n那说明读到了完整行,怎么返回该行信息呢,其实很简单,只用把原本的
            \r\n转换成\0\0,string读到文件结束符就直到是字符串解为了,就能把这一行完整读出来
            同时,检查的字符移动到下一行行首
            */
            else if (m_read_buf[m_checked_idx + 1] == '\n')
            {
                m_read_buf[m_checked_idx++] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;//其余情况都属于读取除了错误
        }
        /*如果\r\n是成对出现的,为什么会有检测到\n而没有检测到\r的情况呢,这里面有两种可能:
        1.文件出错了 2.上依次数据报刚好传到\r终止了
        这需要判断上一个是不是'\r',如果是,那么如同上面一样把\r\n制成\0返回读取成功LINE_OK
        如果不是,那就是文件出错了返回LINE_BAD
        */
        else if (temp == '\n')
        {
            if (m_checked_idx > 1 && m_read_buf[m_checked_idx - 1] == '\r')
            {
                m_read_buf[m_checked_idx - 1] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }
    return LINE_OPEN;
}

//循环读取客户数据，直到无数据可读或对方关闭连接
//非阻塞ET工作模式下，需要一次性将数据读完
bool http_conn::read_once()
{
    if (m_read_idx >= READ_BUFFER_SIZE)
    {
        return false;
    }
    int bytes_read = 0;

    //LT读取数据
    if (0 == m_TRIGMode)
    {
        bytes_read = recv(m_sockfd, m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx, 0);
        m_read_idx += bytes_read;

        if (bytes_read <= 0)
        {
            return false;
        }

        return true;
    }
    //ET读数据
    else
    {
        while (true)
        {
            bytes_read = recv(m_sockfd, m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx, 0);
            if (bytes_read == -1)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;
                return false;
            }
            else if (bytes_read == 0)
            {
                return false;
            }
            m_read_idx += bytes_read;
        }
        return true;
    }
}

//解析http请求行，获得请求方法，目标url及http版本号
http_conn::HTTP_CODE http_conn::parse_request_line(char *text)
{
    /*strpbrk函数,对text字符串进行查找,找后" \t"中的其中一个字符后,
    返回该字符位置,如果没有找到返回NULL
    */
    m_url = strpbrk(text, " \t");
    if (!m_url) //如果没找到,说明请求出现了错误
    {
        return BAD_REQUEST;
    }
    *m_url++ = '\0';//找到后,和parse_line()的方法一样把字符串分离出来
    //储存请求方法,只支持GET/POST,其他方法都返回BAD_REQUEST
    char *method = text;
    if (strcasecmp(method, "GET") == 0)
        m_method = GET;
    else if (strcasecmp(method, "POST") == 0)
    {
        m_method = POST;
        cgi = 1;
    }
    else
        return BAD_REQUEST;
    /* eg/index.html HTTP/1.1
    查找version信息,因为url所对应的起始位置就是url的字段,不用再查找了
    这里strspn实际上是冗余的,检查m_url对应的字符串时候有' \t'中元素组成的前缀,
    如果有跳过这些,但因为上面++的操作已经跳过了空格,所以这里不应该有前缀,也就是会+0.
    */
    m_url += strspn(m_url, " \t");
    m_version = strpbrk(m_url, " \t");
    if (!m_version)
        return BAD_REQUEST;
    *m_version++ = '\0';
    m_version += strspn(m_version, " \t");
    if (strcasecmp(m_version, "HTTP/1.1") != 0)//只接受HTTP/1.1的版本
        return BAD_REQUEST;
    //如果有http://前缀,跳过该前缀直接解析具体要访问的文件位置
    if (strncasecmp(m_url, "http://", 7) == 0)
    {
        m_url += 7;
        m_url = strchr(m_url, '/');
    }
    //如果有https://前缀,跳过该前缀直接解析具体要访问的文件位置
    if (strncasecmp(m_url, "https://", 8) == 0)
    {
        m_url += 8;
        m_url = strchr(m_url, '/');
    }
    //只能接受访问目录(也就是所有资源起始都放在了根目录)
    if (!m_url || m_url[0] != '/')
        return BAD_REQUEST;
    //当url为/时，显示判断界面
    if (strlen(m_url) == 1)
        strcat(m_url, "judge.html");
    //解析完成,转换主状态机状态为CHECK_STATE_HEADER
    m_check_state = CHECK_STATE_HEADER;
    return NO_REQUEST;//没有完整解析完整个http请求,所以此处仍然返回解析不完整
}
/*解析http请求的一个头部信息
目前只能接受Connection,Content-length,Host,这三个请求头信息
*/
http_conn::HTTP_CODE http_conn::parse_headers(char *text)
{
    //解析到了请求头末尾,如果content_length!=0也就是说有请求体信息
    //那么切换主状态机为CHECK_STATE_CONTENT状态,并且返回解析不完整,仍需继续解析
    //如果content_length=0,那么说明解析完整了.
    if (text[0] == '\0')
    {
        if (m_content_length != 0)
        {
            m_check_state = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        return GET_REQUEST;
    }
    else if (strncasecmp(text, "Connection:", 11) == 0)
    {
        text += 11;
        text += strspn(text, " \t");
        if (strcasecmp(text, "keep-alive") == 0)
        {
            m_linger = true;//如果keep-alive的话,仍然保持连接
        }
    }
    else if (strncasecmp(text, "Content-length:", 15) == 0)
    {
        text += 15;
        text += strspn(text, " \t");
        m_content_length = atol(text);//如果有请求体长度,读取该长度
    }
    else if (strncasecmp(text, "Host:", 5) == 0)
    {
        text += 5;
        text += strspn(text, " \t");//访问的ip地址
        m_host = text;
    }
    else
    {
        LOG_INFO("oop!unknow header: %s", text);
    }
    return NO_REQUEST;
}

//判断http请求是否被完整读入
http_conn::HTTP_CODE http_conn::parse_content(char *text)
{
    /*m_read_idx: 读取到的数据长度
      m_content_length: 请求体长度
      m_checked_idx: 已经检查了的字符索引
      这个if判断的就是如果这个数据报包含了完整的数据,那么在第m_content_legnth
      的地方加上结束符号,这样前面全部都是清请求体内容
    */
    if (m_read_idx >= (m_content_length + m_checked_idx))
    {
        text[m_content_length] = '\0';
        //POST请求中最后为输入的用户名和密码
        //用m_string记录请求体中的内容,后面du_request就是解析请求体
        m_string = text;
        return GET_REQUEST;
    }
    return NO_REQUEST;
}

/*返回一个状态码,反馈本次解析成功与否,
或者出现了什么状况
*/
http_conn::HTTP_CODE http_conn::process_read()
{
    //行状态默认是:读到一个完整行
    LINE_STATUS line_status = LINE_OK;
    /*return的默认值设为请求不完整,这是因为正常会有一个返回口,
    返回获得了完整请求.如果因为某些意外情况,直接返回了ret,那必然
    没有通过正常返回口返回,应该是一个有问题的状态,所以初始化成NO_REQUEST.
    */
    HTTP_CODE ret = NO_REQUEST; 
    char *text = 0; //已经解析到了的字符位置
    /*m_check_state: 主状态机当前所处的状态,共有三种
    CHECK_STATE_REQUESTLINE 当前正在分析请求行; CHECK_STATE_HEADER 当前正在分析请求头; CHECK_STATE_CONTENT 当前正在分析请求体
    c++和python一样,如果逻辑运算符已经可以确定返回值了,就不再向后执行.也就是说,只有m_check_state不是
    CHECK_STATE_CONTENT的时候才会下面解析一行;
    m_check_state初始化是CHECK_STATE_REQUESTLINE解析请求行
    */
    /*最终这个while的翻译就是:以下两种情况会进入循环
    1.主状态机处于解析请求体状态,并且前面的解析全部成功
    2.主状态机处于解析请求行/请求头状态,当前行解析成功
    */
    while ((m_check_state == CHECK_STATE_CONTENT && line_status == LINE_OK) || //
            ((line_status = parse_line()) == LINE_OK))
    {
        //返回的那个前行首地址,因为换行符的地方已经被parse_line()制成了/0
        //所以直接可以读取出该行数据
        text = get_line();
        //刷新行首为下一行的首元素,对本次解析不影响但保证了下一次get_line的正确性
        m_start_line = m_checked_idx;
        LOG_INFO("%s", text); //写日志
        switch (m_check_state)
        {
        case CHECK_STATE_REQUESTLINE://如果是处于解析请求行状态
        {   //调用解析请求行的从状态机解析字符串
            ret = parse_request_line(text);
            if (ret == BAD_REQUEST)
                return BAD_REQUEST;
            break;
        }
        case CHECK_STATE_HEADER://如果是处于解析请求头状态
        {   //调用解析请求行头从状态机解析字符串
            ret = parse_headers(text);
            if (ret == BAD_REQUEST)
                return BAD_REQUEST;
            else if (ret == GET_REQUEST)
            {
                return do_request(); //到这里是得到了完整的请求,执行业务逻辑的过程
            }
            break;
        }  //这个似乎才是最复杂的部分(do_request有120行代码,
           //后续加内容也主要是在这里加)
        case CHECK_STATE_CONTENT://如果是处于解析请求体状态
        {   //调用解析请求行体从状态机解析字符串
            ret = parse_content(text);
            if (ret == GET_REQUEST)
                return do_request(); //到这里是得到了完整的请求,执行业务逻辑的过程
            line_status = LINE_OPEN;
            break;
        }
        default:
            return INTERNAL_ERROR;
        }
    }
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::do_request()
{
    //把根目录路径拷贝到m_real_file中
    //doc_root:根目录的绝对路径,也就是存放服务子资源的地方
    //eg. /home/qxy/Desktop/Job/TinyWebServer/TinyWebServer-master/root
    strcpy(m_real_file, doc_root);
    int len = strlen(doc_root);
    //m_url:根目录下的相对地址eg/1; /2 
    //p指向m_url中第一个'/'的地址
    const char *p = strrchr(m_url, '/'); //客户端对应的根目录输入
    
    //处理cgi; cgi默认为0(GET),如果是POST请求,cgi为1
    //使用post请求传递消息,并且/后面的是2(登陆) 3(注册)(要和数据库连接池进行交互)
    if (cgi == 1 && (*(p + 1) == '2' || *(p + 1) == '3'))
    {
        
        //根据标志判断是登录检测还是注册检测
        char flag = m_url[1];
        //m_url_real 所需要访问的文件的真实的相对路径(这一点从下面比较简单的分支看的更清楚)
        /*m_url:eg: /2CGISQL.cgi
        strcpy():把后面的字符串复制到前面的地址空间内,句中意思是m_url_real首元素置为'/'
        strcat:把右边的元素粘到左边,句中意思是/2or/3后面的内容
        strncpy:复制n个字符过来,具有意思是组成绝对路径
        */
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/");
        strcat(m_url_real, m_url + 2);
        strncpy(m_real_file + len, m_url_real, FILENAME_LEN - len - 1);
        free(m_url_real);
        //将用户名和密码提取出来
        //user=123&passwd=123
        //m_string已经解析了的http请求中的请求体内容
        char name[100], password[100];
        int i;
        //请求体中读取name,以&结尾
        for (i = 5; m_string[i] != '&'; ++i)
            name[i - 5] = m_string[i];
        name[i - 5] = '\0';
        //从请求体中读取password,以\0结尾
        int j = 0;
        for (i = i + 10; m_string[i] != '\0'; ++i, ++j)
            password[j] = m_string[i];
        password[j] = '\0';
        //3代表注册
        if (*(p + 1) == '3')
        {
            //如果是注册，先检测数据库中是否有重名的
            //没有重名的，进行增加数据
            char *sql_insert = (char *)malloc(sizeof(char) * 200);
            strcpy(sql_insert, "INSERT INTO user(username, passwd) VALUES(");
            strcat(sql_insert, "'");
            strcat(sql_insert, name);
            strcat(sql_insert, "', '");
            strcat(sql_insert, password);
            strcat(sql_insert, "')");
            /*users.find()是map中的一个调用函数,该函数作用是
            找到map中name的位置,如果不存在,返回的位置就是users.end()
            users.find(name) == users.end()表示名字不在sql中
            */
            if (users.find(name) == users.end())
            {
                /*数据库是属于共享资源,如果删除和查询同时操作容易造成信息的错误
                因此使用进程锁保证查询的时候没有其他进程干扰.
                如果名字不在sql中,通过mysql_query语句向sql插入数据
                */
                m_lock.lock();
                int res = mysql_query(mysql, sql_insert);
                users.insert(pair<string, string>(name, password));
                m_lock.unlock();
                //对于mysql_query,如果执行成功,返回0,http返回登陆页面
                //如果执行失败,返回一个非0值,http返回注册失败页面
                if (!res)
                    strcpy(m_url, "/log.html");
                else
                    strcpy(m_url, "/registerError.html");
            }
            else
                strcpy(m_url, "/registerError.html");
        }
        //2代表登陆.如果是登录，直接判断
        //若浏览器端输入的用户名和密码在表中可以查找到，返回1，否则返回0
        else if (*(p + 1) == '2')
        {
            //先判断name在不在map里,再判断users[name]密码正不正确
            if (users.find(name) != users.end() && users[name] == password)
                strcpy(m_url, "/welcome.html");
            else
                strcpy(m_url, "/logError.html");
        }
    }

    if (*(p + 1) == '0')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/register.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else if (*(p + 1) == '1')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/log.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else if (*(p + 1) == '5')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/picture.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else if (*(p + 1) == '6')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/video.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else if (*(p + 1) == '7')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/fans.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else
        /*如果以上均不符合,即不是登陆也不是注册,直接将url和网站目录拼接
        m_real_file 存放根目录路径
        m_real_file+len也就是在根目录后面追加地址,这里直接把m_url地址追加进去了
        因为m_real_file初始化的时候是用全\0初始化的,所以不用担心结束符问题
        */
        strncpy(m_real_file + len, m_url, FILENAME_LEN - len - 1);
    //stat:获取m_real_file中的文件状态,存到m_file_stat里面.
    //如果成功会返回0,失败会返回-1(失败就是找不到对应文件)
    if (stat(m_real_file, &m_file_stat) < 0)
        return NO_RESOURCE;

    if (!(m_file_stat.st_mode & S_IROTH)) //如果其他用户没有读的权限说明是禁止请求的资源
        return FORBIDDEN_REQUEST;

    if (S_ISDIR(m_file_stat.st_mode)) //如果是个文件夹而不是文件,那么请求有问题
        return BAD_REQUEST;

    int fd = open(m_real_file, O_RDONLY);//使用open打开文件
    /*mmap 内存映射函数,把磁盘文件映射到内存,这样修改内存就能修改文件.
    mmap(void* start, size_t length, int prot, int flags, int fd, off_t offset);
    start:映射区的起始地址,0表示系统指定. legnth: 映射去长度, port:期望的内存保护标志,不能和打开模式向冲突
    PORT_READ: 页内容可以被读取. MAP_PRIVATE //建立一个写入时拷贝的私有映射。内存区域的写入不会影响到原文件。这个标志和以上标志是互斥的，只能使用其中一个。
    这里和传统内存映射不同,不是要修改文件,而是把fd指向的文件资源搬到内存中去(为了后面传输除去).
    现在m_file_address就指向着一片内存空间,包含了要传输的文件.
    */
    m_file_address = (char *)mmap(0, m_file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return FILE_REQUEST;
}
void http_conn::unmap()
{
    if (m_file_address)
    {
        munmap(m_file_address, m_file_stat.st_size);
        m_file_address = 0;
    }
}
bool http_conn::write()
{
    int temp = 0;

    if (bytes_to_send == 0)
    {
        modfd(m_epollfd, m_sockfd, EPOLLIN, m_TRIGMode);
        init();
        return true;
    }

    while (1)
    {
        //writev:将驻留在两个或多个不连续缓冲区的数据一次性写出去
        //temp表示写出去的数据长度
        temp = writev(m_sockfd, m_iv, m_iv_count);
        //小于0是出错了
        if (temp < 0)
        {
            if (errno == EAGAIN)
            {
                modfd(m_epollfd, m_sockfd, EPOLLOUT, m_TRIGMode);
                return true;
            }
            unmap();//释放请求体的内存位置
            return false;//返回写失败
        }
        //每写一部分都要动态修改记录内存首地址的指针和剩余数据长度
        bytes_have_send += temp;
        bytes_to_send -= temp;
        if (bytes_have_send >= m_iv[0].iov_len)
        {
            m_iv[0].iov_len = 0;
            m_iv[1].iov_base = m_file_address + (bytes_have_send - m_write_idx);
            m_iv[1].iov_len = bytes_to_send;
        }
        else
        {
            m_iv[0].iov_base = m_write_buf + bytes_have_send;
            m_iv[0].iov_len = m_iv[0].iov_len - bytes_have_send;
        }
        //如果发送完了
        if (bytes_to_send <= 0)
        {
            unmap();//释放请求体的内存位置
            modfd(m_epollfd, m_sockfd, EPOLLIN, m_TRIGMode);

            if (m_linger)//如果是保持连接的话,那么该http连接初始化但是文件描述符不释放
            {
                init();
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
//往写缓冲中写入待发送的数据
bool http_conn::add_response(const char *format, ...)
{   //如果目前写入的数据已经超过了写缓冲池上限,那么无法再写入
    //因此返回false,写入失败
    /*这个函数主要是为了操作格式化的字符串，vsprintf就类似于printf
    注意format不是可变参数,format就是"%s %d %s\r\n"一类,后面的...才是可变参数
    通过va_start(arg_list,format)利用format的地址位置(后移指针)才找的到可变参数首地址
    也就是不调用va_start是找不到可变参数的
    */

    if (m_write_idx >= WRITE_BUFFER_SIZE)
        return false;
    va_list arg_list;//声明一个指针
    //arg_list指针指向可变参数的首地址,这里和format本身没啥关系,因为format后是可变参数首地址,
    //所以需要通过format找到可变参数的首地址
    va_start(arg_list, format); 
    /*vsnprintf:
    m_write_buf+m_write_idx:指向缓冲区的指针,写入起始地址,
    WRITE_BUFFER_SIZE-1-m_write_idx:写入的最大长度
    vsnprintf做的事情类似printf,将format所规定的格式,把可变参数列表中的元素组合起来
    不同之处是printf把它打印在输出端,而vsnprintf把它添加在指定的地址后面
    本例中是m_write_buf + m_write_idx
    */
    int len = vsnprintf(m_write_buf + m_write_idx, WRITE_BUFFER_SIZE - 1 - m_write_idx, format, arg_list);
    if (len >= (WRITE_BUFFER_SIZE - 1 - m_write_idx))
    { //如果超过写入上限,报错
        va_end(arg_list);
        return false;
    }
    m_write_idx += len;
    va_end(arg_list);//释放内存

    LOG_INFO("request:%s", m_write_buf);//添加日志

    return true;//写入成功
}
//添加请求行数据,因为协议永远是http/1.1所以不作为参数传进来,传的是状态码和状态码解释
bool http_conn::add_status_line(int status, const char *title)
{
    //add_response就是利用了vsprintf()把传进取的格式化字符串按序排列到
    //写缓冲区
    return add_response("%s %d %s\r\n", "HTTP/1.1", status, title);
}
bool http_conn::add_headers(int content_len)
{
    return add_content_length(content_len) && add_linger() &&
           add_blank_line();
}
//增加请求头,内容为:content-length:number
//number是请求体的长度
bool http_conn::add_content_length(int content_len)
{   
    return add_response("Content-Length:%d\r\n", content_len);
}
bool http_conn::add_content_type()
{
    return add_response("Content-Type:%s\r\n", "text/html");
}
//增加linger属性,如果m_linger是true,则为keep-alive,else是close
bool http_conn::add_linger()
{
    return add_response("Connection:%s\r\n", (m_linger == true) ? "keep-alive" : "close");
}
//增加空行,空行后面是请求体的内容
bool http_conn::add_blank_line()
{
    return add_response("%s", "\r\n");
}
bool http_conn::add_content(const char *content)
{
    return add_response("%s", content);
}
bool http_conn::process_write(HTTP_CODE ret)
{
    switch (ret)
    {
    case INTERNAL_ERROR:
    {
        add_status_line(500, error_500_title);
        add_headers(strlen(error_500_form));
        if (!add_content(error_500_form))
            return false;
        break;
    }
    case BAD_REQUEST:
    {
        add_status_line(404, error_404_title);
        add_headers(strlen(error_404_form));
        if (!add_content(error_404_form))
            return false;
        break;
    }
    case FORBIDDEN_REQUEST:
    {
        add_status_line(403, error_403_title);
        add_headers(strlen(error_403_form));
        if (!add_content(error_403_form))
            return false;
        break;
    }
    case FILE_REQUEST: //如果是请求了某一个指定的文件,就把这个网页文件传递到客户端.
    {
        add_status_line(200, ok_200_title);//响应行是http/1.1 200 ok
        if (m_file_stat.st_size != 0) //如果要传输的文件长度>0(即有响应体中有数据要传输)
        {   /*这里蕴含了WRITE_BUFFER_SIZE的写缓冲只是请求头+请求行大小,响应体直接从磁盘搬到内存
            再通过内存写过去.这样做我认为是因为响应体的大小变化很大,不好预测.如果同时写到写缓冲里面
            写缓冲开小了容易出bug,开大了在大多数时候又浪费空间.
            */
            add_headers(m_file_stat.st_size);
            m_iv[0].iov_base = m_write_buf;
            m_iv[0].iov_len = m_write_idx;
            m_iv[1].iov_base = m_file_address;
            m_iv[1].iov_len = m_file_stat.st_size;
            m_iv_count = 2;
            bytes_to_send = m_write_idx + m_file_stat.st_size;
            return true;
        }
        else//如果有响应体内容要传输,就传输<html><body></body></html>这样一个文件了.(解析出来就是一个空网页)
        {
            const char *ok_string = "<html><body></body></html>";
            add_headers(strlen(ok_string));
            if (!add_content(ok_string))
                return false;
        }
    }
    default:
        return false;
    }
    m_iv[0].iov_base = m_write_buf;
    m_iv[0].iov_len = m_write_idx;
    m_iv_count = 1;
    bytes_to_send = m_write_idx;
    return true;
}
/*这里是整个程序对后续扩展比较重要的地方,解析客户端报文段请求,
从服务端把资源上传到客户端.
*/
void http_conn::process()
{
    HTTP_CODE read_ret = process_read();//解析http请求
    if (read_ret == NO_REQUEST)//如果是没有解析到完整请求,
    {   //重置改连接,接收读请求.因为服务端一般不会主动进行写请求的,要先被请求再传数据
        //TRIGMode: 触发模式
        modfd(m_epollfd, m_sockfd, EPOLLIN, m_TRIGMode);
        return;
    }
    bool write_ret = process_write(read_ret);//把数据写入写缓存
    if (!write_ret)
    {
        close_conn();
    }
    //如果写入缓存成功,把文件描述符改成写请求,重新加入请求队列里面.
    modfd(m_epollfd, m_sockfd, EPOLLOUT, m_TRIGMode);
}
