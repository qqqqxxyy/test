#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include "log.h"
#include <pthread.h>
using namespace std;
//这个日志系统就两个函数,一个是初始化函数,一个是记录函数
Log::Log()
{
    m_count = 0;
    m_is_async = false;
}

Log::~Log()
{
    if (m_fp != NULL)
    {
        fclose(m_fp);
    }
}
/*异步需要设置阻塞队列的长度，同步不需要设置
参数("./ServerLog", m_close_log, 2000, 800000, 800);
file_name:储存日志的文件名;2000 ,split_lines:80000  , max_queue_size:800:最大日志缓冲队列
*/
bool Log::init(const char *file_name, int close_log, int log_buf_size, int split_lines, int max_queue_size)
{
    //如果设置了max_queue_size,则说明有缓冲队列,也就是设置为异步IO模式
    if (max_queue_size >= 1)
    {
        m_is_async = true; //异步标志位制为True
        //定义一个阻塞队列,阻塞队列的特性就是,如果队列中没有元素,执行pop会被挂起
        //当队列满的时候,执行push也会被挂起
        m_log_queue = new block_queue<string>(max_queue_size); 
        pthread_t tid;
        //flush_log_thread为回调函数,这里表示创建线程异步写日志
        //创建一个写日志的线程
        pthread_create(&tid, NULL, flush_log_thread, NULL);
    }
    //0开启日志,1关闭日志,因为默认开启日志才会来到init函数中,所以实际没啥意义.
    m_close_log = close_log;
    //日志缓冲池大小
    m_log_buf_size = log_buf_size;
    m_buf = new char[m_log_buf_size];//缓冲数组,全部制为\0
    memset(m_buf, '\0', m_log_buf_size);
    m_split_lines = split_lines;
    //NULL是传出参数,如果是NULL则返回一个时间,
    //如果是个time_t的指针,则把时间传到t上面
    //返回的是日历时间(calendar time)从1970.1.1开始的秒数
    time_t t = time(NULL);
    //把日里时间转换为本体时间(XX年XX月XX日)
    struct tm *sys_tm = localtime(&t);
    //my_tm里的内容就是本地时间
    struct tm my_tm = *sys_tm;

    //返回第一个'/'出现的地址,储存在p里面,也就是P可以读取到的是ServerLog
    const char *p = strrchr(file_name, '/');
    char log_full_name[256] = {0};

    if (p == NULL)
    {   //如果没有找到'/',说明filename就是文件名,把日起和文件名结合储存在snprintf里
        snprintf(log_full_name, 255, "%d_%02d_%02d_%s", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, file_name);
    }
    else
    {   //如果有找到'/',那p+1之后的内容是文件名,把文件名复制到log_name之中
        strcpy(log_name, p + 1);
        strncpy(dir_name, file_name, p - file_name + 1);//把P之前的路径占到dir上,作为路径名字
        //路径+时间+文件名
        snprintf(log_full_name, 255, "%s%d_%02d_%02d_%s", dir_name, my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, log_name);
    }

    m_today = my_tm.tm_mday;
    //打开所指定的文件路径,以追加的形式(如果没有则创建一个)
    m_fp = fopen(log_full_name, "a");
    if (m_fp == NULL)
    {
        return false;//如果打开失败,返回false
    }
    //后面就用文件描述符m_fp来通信了.
    return true;//否则返回成功
}
/*level:日志类型
0:debug; 1:info; 2:warn; 3:info
*/
void Log::write_log(int level, const char *format, ...)
{
    //这个地方写的明显冗余了,直接一个time一个localtime就可以转化的事情
    //还要高个timeval结构体,最后也没有利用到里面的微妙精度
    struct timeval now = {0, 0};//初始化一个timeval结构体变量(储存tv_sec, tv_usec)
    gettimeofday(&now, NULL);//返回当前距离1970年的秒数和微秒数,储存在now里(now是传出参数)
    time_t t = now.tv_sec; //取出秒数,存在t中
    //localtime:将t所代表的秒数转换成tm结构体,sys_tm指针指向这个结构体
    struct tm *sys_tm = localtime(&t);
    struct tm my_tm = *sys_tm;
    char s[16] = {0};
    switch (level)//根据等级确定日志头
    {
    case 0:
        strcpy(s, "[debug]:");
        break;
    case 1:
        strcpy(s, "[info]:");
        break;
    case 2:
        strcpy(s, "[warn]:");
        break;
    case 3:
        strcpy(s, "[erro]:");
        break;
    default://如果不再0123里面,就还是info类型
        strcpy(s, "[info]:");
        break;
    }
    //写入一个log，对m_count++, m_split_lines最大行数
    //写文件的时候肯定是加个锁保险,但其实如果不使用线程池进行log写操作的化,
    //是不存在资源同步的问题的.(同步就不说了,这里异步也是只用一个线程处理,不是放进线程池里,
    //所以没有线程同步问题)
    m_mutex.lock();
    m_count++;
    /*这个判断是对于24小时不停机的服务器,如果运行到了第二天,要重新创建当日文件,在新文件中记录日志
    日期存储在m_today之中
    */
    if (m_today != my_tm.tm_mday || m_count % m_split_lines == 0) //everyday log
    {
        
        char new_log[256] = {0};
        fflush(m_fp);
        fclose(m_fp);
        char tail[16] = {0};
       
        snprintf(tail, 16, "%d_%02d_%02d_", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday);
       
        if (m_today != my_tm.tm_mday)
        {
            snprintf(new_log, 255, "%s%s%s", dir_name, tail, log_name);
            m_today = my_tm.tm_mday;
            m_count = 0;
        }
        else
        {
            snprintf(new_log, 255, "%s%s%s.%lld", dir_name, tail, log_name, m_count / m_split_lines);
        }
        m_fp = fopen(new_log, "a");
    }
 
    m_mutex.unlock();

    /*这里要格式化读取字符串,我起始觉得,封装一个专门用来格式化字符串的函数,
    会阅读起来更舒服.
    */
    va_list valst; //一个宏定义的指针
    va_start(valst, format); //把format后面的首地址(可变参数的首地址),付给valst

    string log_str; //待写入的字符串
    m_mutex.lock();

    //写入的具体时间内容格式
    //把时间读进m_buf里面,因为就一个m_buf,所以m_buf也属于共享资源
    int n = snprintf(m_buf, 48, "%d-%02d-%02d %02d:%02d:%02d.%06ld %s ",
                     my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday,
                     my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, now.tv_usec, s);
    /*首地址m_buf+n,长度m_log_bug_size-1,格式化字符串format,后面的具体格式内容,通过valst所记录的
    地址一个一个寻找,填进里面.
    */
    int m = vsnprintf(m_buf + n, m_log_buf_size - 1, format, valst);
    m_buf[n + m] = '\n'; 
    m_buf[n + m + 1] = '\0'; //加个换行符和文件结束副
    log_str = m_buf;

    m_mutex.unlock();
    //如果异步,并且日志队列没满,压进队列里
    if (m_is_async && !m_log_queue->full())
    {//这个队列这里怎么能不上锁呢,如果前面都上锁这里也应该有锁
        m_log_queue->push(log_str);
    }
    else
    {//否则,在本线程里执行文件流输出的操作
        m_mutex.lock();
        fputs(log_str.c_str(), m_fp);
        m_mutex.unlock();
    }

    va_end(valst);
}

void Log::flush(void)
{
    m_mutex.lock();
    //强制刷新写入流缓冲区
    fflush(m_fp);
    m_mutex.unlock();
}
