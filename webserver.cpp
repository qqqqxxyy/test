#include "webserver.h"

WebServer::WebServer()
{
    //http_conn类对象
    //创建一个对象数组,结构体数组要用new
    users = new http_conn[MAX_FD];

    //设置root文件夹路径
    char server_path[200];
    getcwd(server_path, 200);//当前文件夹为root文件夹路径
    char root[6] = "/root";
    m_root = (char *)malloc(strlen(server_path) + strlen(root) + 1);
    strcpy(m_root, server_path);
    strcat(m_root, root);
    //最终得到root的绝对路径
    // /home/qxy/Desktop/Job/TinyWebServer/TinyWebServer-master/root

    //定时器
    users_timer = new client_data[MAX_FD];
}

WebServer::~WebServer()
{
    close(m_epollfd);
    close(m_listenfd);
    close(m_pipefd[1]);
    close(m_pipefd[0]);
    delete[] users;
    delete[] users_timer;
    delete m_pool;
}

//init的功能就是把这些从命令行读取的或者默认值的参数都记录起来
void WebServer::init(int port, string user, string passWord, string databaseName, int log_write, 
                     int opt_linger, int trigmode, int sql_num, int thread_num, int close_log, int actor_model)
{   
    m_port = port;
    m_user = user;
    m_passWord = passWord;
    m_databaseName = databaseName;
    m_sql_num = sql_num;
    m_thread_num = thread_num;
    m_log_write = log_write;
    m_OPT_LINGER = opt_linger;
    m_TRIGMode = trigmode;
    m_close_log = close_log;
    m_actormodel = actor_model;
}

void WebServer::trig_mode()
{
    //LT + LT
    if (0 == m_TRIGMode)
    {
        m_LISTENTrigmode = 0;
        m_CONNTrigmode = 0;
    }
    //LT + ET
    else if (1 == m_TRIGMode)
    {
        m_LISTENTrigmode = 0;
        m_CONNTrigmode = 1;
    }
    //ET + LT
    else if (2 == m_TRIGMode)
    {
        m_LISTENTrigmode = 1;
        m_CONNTrigmode = 0;
    }
    //ET + ET
    else if (3 == m_TRIGMode)
    {
        m_LISTENTrigmode = 1;
        m_CONNTrigmode = 1;
    }
}

void WebServer::log_write()
{
    if (0 == m_close_log) //如果日志系统是关闭状态,则不做任何处理
    {
        //初始化日志
        if (1 == m_log_write)//如果是异步日志,init最后一个参数制为800
        /*参数分别为:'./ServerLog':文件名
        m_close_log:开启日志系统的符号位
        2000: log_buf_size 日志缓冲大小
        8000000: 最大行数
        800/0: 待记录日志队列 (异步日志有意义)
        */
            Log::get_instance()->init("./ServerLog", m_close_log, 2000, 800000, 800);
        else//如果是同步日志,最后一个参数制为0
            Log::get_instance()->init("./ServerLog", m_close_log, 2000, 800000, 0);
    }
}

void WebServer::sql_pool()
{
    //初始化数据库连接池(单例模式)
    m_connPool = connection_pool::GetInstance();//调用connection_pool类中的静态函数
    //数据库连接池中初始化函数对数据库连接池进行初始化
    //预先创建好maxConn个数据库连接.
    m_connPool->init("localhost", m_user, m_passWord, m_databaseName, 3306, m_sql_num, m_close_log);

    //初始化数据库读取表
    //http请求队列的第一个请求获得用户名-密码表
    //这里就是只改了类中首元素的地址
    users->initmysql_result(m_connPool);
}

void WebServer::thread_pool()
{
    //线程池
    /*这句话首先里面(m_actormodel,m_connPool,m_thread_num)分别传递的是:
    m_actormodel: 并发模式 0-模拟proactor模型 1-reactor模型
    m_connPool: 访问数据库的指针
    m_thread_num: 创建的线程数量,从thread_num中读取,可以通过-t从命令行修改
    threadpool<http_conn>: http_conn意思是threadpool类中有一个模板类T,
    实例化的时候指定http_coon代表所有的T
    */
    m_pool = new threadpool<http_conn>(m_actormodel, m_connPool, m_thread_num);
}
/*创建 监听端口 开始监听通信,
创建 内核事件 表进行I/O多路复用
总结:设计好主线程*/
void WebServer::eventListen()
{
    //网络编程基础步骤 
    /*返回用于套接字通信的文件描述符储存为m_listenfd,
    PF_INET:通信用IPv4协议族,SOCK_STREAM:流式服务
    */
    m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_listenfd >= 0);

    //0:使用优雅关闭连接 1:不使用优雅关闭连接 
    //优雅关闭连接 opt_linger
    /*setsockopt是一个设置套接字属性的函数,只不过之前一直被用来做端口复用的功能,
    这里就也拿来设置是否优雅关闭连接.
    SOL_SOCKET:系统中解释选项的代码为套接字代码(一般都这么设置)
    */
    /*close(m_listendf)缺省行为是四次挥手关闭
    但可以通过SO_LINGER设置为:立即关闭/等待一段时间之后立即关闭
    struct linger tmp = {0, 1}; 第一个参数是否设置关闭行为.0代表不设置,即缺省的关闭方式,四次挥手.
    struct linger tmp = {1, 1}; 1代表设置,即打开.1代表等1秒立即关闭(给1秒发数据的时间)
    */
    if (0 == m_OPT_LINGER)
    {
        struct linger tmp = {0, 1};//优雅关闭
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }
    else if (1 == m_OPT_LINGER)
    {
        struct linger tmp = {1, 1};//等一秒立即关闭
        setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    }

    int ret = 0;
    /*设置与套接字绑定的地址和端口,
    地址:INADDR_ANY本地所有地址
    端口:m_port默认9006,也可以从命令行通过-p指定
    */
    struct sockaddr_in address;
    //bzero将address中的空间全部制为\0
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(m_port);

    int flag = 1;
    //端口复用
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    //绑定套接字
    ret = bind(m_listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret >= 0);
    ret = listen(m_listenfd, 5);
    assert(ret >= 0);
    //处理信号函数,设置信号,计时等等工具任务
    utils.init(TIMESLOT);

    //epoll创建内核事件表
    /*MAX_EVENT_NUMBER 接受同时管理的最大事件数 默认10000
    epoll_evenet 里面有一个ev events变量,内容是对应文件描述符的检测事件
    EPOLLIN/EPOLLOUT (读写事件)以及EPOLLET(边沿触发模式)
    在event_loop中的 epoll_wait()函数中被调用,用来储存被触发的epoll事件.*/
    epoll_event events[MAX_EVENT_NUMBER];
    /*epoll_create: 创建内核事件表,返回一个文件描述符m_epollfd,
    通过m_epollfd操作内核事件表*/
    m_epollfd = epoll_create(5);
    assert(m_epollfd != -1);
    /*m_LISTENTrigmode监听事件的触发模式:0(默认):LT;1:ET
    m_CONNTrigmode连接事件的触发模式:0(默认):LT;1:ET
    第三个选项是oneshot选项,默认关闭*/
    //把listenfd的读事件加进内核事件表中
    utils.addfd(m_epollfd, m_listenfd, false, m_LISTENTrigmode);
    //指定http_conn中的静态类变量
    http_conn::m_epollfd = m_epollfd;
    /*创建一对 无名套接字 用于接收系统发送的信号信息
    匿名套接字通信过程:m_pipefd[2]数组代表一组用来通信的文件描述符
    sockpetpair把两个管道连起来
    将pipe[0]注册到内核事件表用来监听(后面会设置,alarm计时器到了,内核的消息都会写到pipe[1]中)
    ,pipe[1]用来通信.有信号要传递的时候,往pipe[1]里写,pipe[0]就会收到消息了.    
    */
    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, m_pipefd);
    assert(ret != -1);
    utils.setnonblocking(m_pipefd[1]);
    utils.addfd(m_epollfd, m_pipefd[0], false, 0);
    //向读端关闭的端口写数据会让内核产生SIGPIPE信号,内核默认处理方式是关掉服务端
    //但这是我们不希望见到的,所以选择忽略信号
    //第三个参数是bool值,不输入默认就是0,SIG_IGN于值函数默认是默认动作调整为忽略.
    utils.addsig(SIGPIPE, SIG_IGN,false);
    //SIGALRM,SIGTERM处理方式都是计时器相关的
    //sighandler的执行逻辑就是把信号传进内部题哦阿接字sock_stream中去
    utils.addsig(SIGALRM, utils.sig_handler, false);//处理动作编程通过套接字发送通知
    utils.addsig(SIGTERM, utils.sig_handler, false);

    alarm(TIMESLOT);//设置定时器时间,每隔TIMESLOT时间向进程发送一个alarm信号

    //工具类,信号和描述符基础操作
    //定义管道文件描述符和epoll文件描述符
    //这些在epoll/管道创建的时候都被唯一指定
    //静态局部变量
    Utils::u_pipefd = m_pipefd;
    Utils::u_epollfd = m_epollfd;
}

//初始化http连接以及初始化定时器类并将该定时器类加入定时器链表中
void WebServer::timer(int connfd, struct sockaddr_in client_address)
{
    /*http连接在时钟内部初始化,这有合理之处也有不合理
    合理之处是,每个连接建立的时候都要初始化时钟,因此可以保证每个连接建立的时候都被初始化
    不合理之处就是不好找,找了半天才发现是在timer里面*/
    /*这里类似哈希数组,connfd所对应的httpconn数组索引就是其连接.所以可以直接通过connfd进行连接初始化.
    */
    users[connfd].init(connfd, client_address, m_root, m_CONNTrigmode, m_close_log, m_user, m_passWord, m_databaseName);
    //初始化client_data数据
    //创建定时器，设置回调函数和超时时间，绑定用户数据，将定时器添加到链表中
    //client_data数组本身只是对连接信息的一种记录,并不是链表结构,它的好处是可以通过
    //connfd快速检索到该连接
    users_timer[connfd].address = client_address;
    users_timer[connfd].sockfd = connfd;
    util_timer *timer = new util_timer; //定时器链表的节点类
    timer->user_data = &users_timer[connfd];
    timer->cb_func = cb_func;//该回调函数用来关闭服务器连接
    time_t cur = time(NULL);
    timer->expire = cur + 3 * TIMESLOT;//生存时间是3个TIMESLOT
    users_timer[connfd].timer = timer;
    utils.m_timer_lst.add_timer(timer);//定时器加入链表
}

//若有数据传输，则将定时器往后延迟3个单位
//并对刷新后的定时器在链表上的位置进行调整
void WebServer::adjust_timer(util_timer *timer)
{
    time_t cur = time(NULL);
    timer->expire = cur + 3 * TIMESLOT;//从新设置超时事件(因为读/写事件被触发了)
    utils.m_timer_lst.adjust_timer(timer);
    //日志记录,调整了一个定时器
    LOG_INFO("%s", "adjust timer once");
}
//从计时器链表中删除该sockfd所对应的计时器
//并且关闭该sockfd连接
void WebServer::deal_timer(util_timer *timer, int sockfd)
{
    timer->cb_func(&users_timer[sockfd]);//使用cb_func关闭sock连接
    if (timer)
    {
        utils.m_timer_lst.del_timer(timer);//从定时器链表中删除该定时器
    }

    LOG_INFO("close fd %d", users_timer[sockfd].sockfd);
}
//接收客户端传来的建立连接请求,创建链接
bool WebServer::dealclinetdata()
{
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address);
    //如果是监听端口是LT模式:
    if (0 == m_LISTENTrigmode)
    {
        //接收客户端请求,将客户端地址信息储存在client_address里,通过connfd与客户端进行通信
        int connfd = accept(m_listenfd, (struct sockaddr *)&client_address, &client_addrlength);
        if (connfd < 0)
        {   //LOG_ERROR是日志语句
            LOG_ERROR("%s:errno is:%d", "accept error", errno);
            return false;
        }
        if (http_conn::m_user_count >= MAX_FD)
        {
            //如果现有连接数过了上限
            //在show_error中,向连接对象发送一个错误信息,然后释放连接(close)
            utils.show_error(connfd, "Internal server busy");
            LOG_ERROR("%s", "Internal server busy");
            return false;
        }//加入计时器
        timer(connfd, client_address);
    }

    else//如果监听端口是ET模式:
    {
        while (1) //这个while就是LT模式和ET模式的不同了
        {
            //如果有多个建立连接的请求同时到达,因为ET只通知一次,所以要循环读取
            //LT模式则不需要循环通知,以为你一次没读完epoll还会继续通知
            int connfd = accept(m_listenfd, (struct sockaddr *)&client_address, &client_addrlength);
            if (connfd < 0)
            {
                LOG_ERROR("%s:errno is:%d", "accept error", errno);
                break;
            }
            if (http_conn::m_user_count >= MAX_FD)
            {
                utils.show_error(connfd, "Internal server busy");
                LOG_ERROR("%s", "Internal server busy");
                break;
            }
            timer(connfd, client_address);
        }
        return false;
    }
    return true;
}
//信号处理函数
bool WebServer::dealwithsignal(bool &timeout, bool &stop_server)
{
    int ret = 0;
    int sig;
    char signals[1024];
    //recv是socket编程专用的io函数,最后一个参数是等待时间
    //但实际上不阻塞的read效果应该是一样的
    //接收pipefd中读缓冲区的数据到signals值中,起始接收到的就是一个整形
    ret = recv(m_pipefd[0], signals, sizeof(signals), 0);
    if (ret == -1)
    {
        return false;
    }
    else if (ret == 0)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < ret; ++i)
        {
            switch (signals[i])
            {
            case SIGALRM://处理SIGALRM信号
            {
                timeout = true;
                break;
            }
            case SIGTERM://处理SIGTERM终止进程信号
            {
                stop_server = true;
                break;
            }
            }
        }
    }
    return true;
}

void WebServer::dealwithread(int sockfd)
{
    util_timer *timer = users_timer[sockfd].timer;

    //reactor模型,数据读取在工作线程内部实现
    if (1 == m_actormodel)
    {
        if (timer)//如果不是空地址,更新计时器.
        {
            adjust_timer(timer);
        }
        //若监测到读事件，将该事件放入请求队列
        //users是http_conn指针,通过+sockfd访问本次
        //读取的http连接的地址
        m_pool->append(users + sockfd, 0);
        while (true)
        {   //在这个循环中循环等待工作线程完成读/写事件,来修改文件描述符表
            //如果工作线程,完成了读事件和一次写事件的时候,improv都会被制为1
            if (1 == users[sockfd].improv)
            {   //如果读写出错了,timer_flag会被制为1,deal_timer会在链表中删除该计时器
                if (1 == users[sockfd].timer_flag)
                {
                    deal_timer(timer, sockfd);
                    users[sockfd].timer_flag = 0;
                }
                //重置improve
                users[sockfd].improv = 0;
                break;
            }
        }
    }
    else
    {
        //proactor模式,数据读取在主线程中执行
        //在主线程中执行http_conn的read_once()操作,然后再将请求放进请求队列
        if (users[sockfd].read_once())
        {
            LOG_INFO("deal with the client(%s)", inet_ntoa(users[sockfd].get_address()->sin_addr));

            //若监测到读事件，将该事件放入请求队列
            m_pool->append_p(users + sockfd);

            if (timer)
            {   //更新计时器
                adjust_timer(timer);
            }
        }
        else
        {   //读出错,则删除计时器并释放连接
            deal_timer(timer, sockfd);
        }
    }
}

void WebServer::dealwithwrite(int sockfd)
{
    util_timer *timer = users_timer[sockfd].timer;
    //reactor
    if (1 == m_actormodel)
    {
        if (timer)
        {
            adjust_timer(timer);
        }

        m_pool->append(users + sockfd, 1);

        while (true)
        {
            if (1 == users[sockfd].improv)
            {
                if (1 == users[sockfd].timer_flag)
                {   //写出错,则删除计时器并释放连接
                    deal_timer(timer, sockfd);
                    users[sockfd].timer_flag = 0;
                }
                users[sockfd].improv = 0;
                break;
            }
        }
    }
    else
    {
        //proactor
        //users[sockfd]指的是要处理的文件描述符的http请求
        if (users[sockfd].write()) //如果返回True,说明文件描述符不释放,连接和时钟信息仍然保留
        {
            LOG_INFO("send data to the client(%s)", inet_ntoa(users[sockfd].get_address()->sin_addr));

            if (timer)
            {
                adjust_timer(timer);
            }
        }
        else//否则就是释放连接,释放时钟和文件描述符
        {
            deal_timer(timer, sockfd);
        }
    }
}

/*主线程维持事件循环,等待epoll_wait通知处理事件
事件包括:建立连接的请求;关闭连接的请求;超时信号处理;读写数据
在检测到读事件的时候,读完数据后通过m_poll->append将线程池事件
添加进请求队列
*/
void WebServer::eventLoop()
{
    bool timeout = false;
    bool stop_server = false;//关闭服务器的信号

    while (!stop_server)
    {
        //epoll_wait m_epollfd:epoll事件表,events->有信号的事件传到这里,
        //events是一个传出参数
        //MAX...最大值,time_out:超时时间,-1表示不阻塞
        int number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
        //EINTER:客户端关闭连接. 要和注册event的时候检测EPOLLRDHUP配套使用
        //errno是定义在宏包里的,epoll_wait出现错误的时候会赋予一个错误号
        if (number < 0 && errno != EINTR)
        {
            LOG_ERROR("%s", "epoll failure");
            break;
        }

        for (int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;//有消息传来的套接字文件描述符

            //处理新到的客户连接
            if (sockfd == m_listenfd)
            {
                //在epoll中注册新链接被集合到了这个程序里面
                bool flag = dealclinetdata();
                if (false == flag)
                    continue;
            }//如果发送来的是客户端关闭连接的请求
            else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                //服务器端关闭对应客户端的连接，并且移除对应的定时器 
                //将链表数组中对应的timer取出来
                util_timer *timer = users_timer[sockfd].timer;
                deal_timer(timer, sockfd);
            }//如果是UNIX套接字发来的数据,一般是SIGALARM信号,将timeout制为1,处理信号
            else if ((sockfd == m_pipefd[0]) && (events[i].events & EPOLLIN))
            {
                bool flag = dealwithsignal(timeout, stop_server);
                if (false == flag)
                    LOG_ERROR("%s", "dealclientdata failure");
            }
            //处理客户连接上接收到的数据
            else if (events[i].events & EPOLLIN)
            {//存在读就绪事件
                dealwithread(sockfd);
            }
            else if (events[i].events & EPOLLOUT)
            {//存在写就绪事件
                dealwithwrite(sockfd);
            }
        }//那这里哦功能alarm起始不如用setitimer
        if (timeout) //如果超时了,执行时钟事件.
        {   //时钟事件是,重置alarm,然后sort_timer_lst执行一个tick
            utils.timer_handler();
            //记录时钟事件
            LOG_INFO("%s", "timer tick");

            timeout = false;
        }
    }
}