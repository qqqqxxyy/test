#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <pthread.h>
#include "block_queue.h"

using namespace std;
//日志系统也是单例模式,和数据库连接池一样,那其实线程池也可以是单例模式咯?
class Log
{
public:
    //C++11以后,使用局部变量懒汉不用加锁
    //这个不是函数指针的意思,而是返回一个静态的Log类指针,是一个实例函数
    static Log* get_instance()
    {
        static Log instance;
        return &instance;
    }

    static void* flush_log_thread(void *args)
    {
        Log::get_instance()->async_write_log();
        return NULL;
    }
    //可选择的参数有日志文件、日志缓冲区大小、最大行数以及最长日志条队列
    bool init(const char *file_name, int close_log, int log_buf_size = 8192, int split_lines = 5000000, int max_queue_size = 0);

    void write_log(int level, const char *format, ...);

    void flush(void);

private:
    Log();
    virtual ~Log();
    void *async_write_log()
    {
        string single_log;
        //从阻塞队列中取出一个日志string，写入文件
        while (m_log_queue->pop(single_log))
        {
            m_mutex.lock();
            //c_str字符数组转字符串
            fputs(single_log.c_str(), m_fp);//写入操作
            m_mutex.unlock();
        }
        return NULL;
    }

private:
    char dir_name[128]; //路径名
    char log_name[128]; //log文件名
    int m_split_lines;  //日志最大行数
    int m_log_buf_size; //日志缓冲区大小
    long long m_count;  //日志行数记录
    int m_today;        //因为按天分类,记录当前时间是那一天
    FILE *m_fp;         //打开log的文件指针
    char *m_buf;
    block_queue<string> *m_log_queue; //阻塞队列
    bool m_is_async;                  //是否同步标志位
    locker m_mutex;
    int m_close_log; //关闭日志
};
//#把write_log函数封装成写不同类型的日志,增加程序可读性.
#define LOG_DEBUG(format, ...) if(0 == m_close_log) {Log::get_instance()->write_log(0, format, ##__VA_ARGS__); Log::get_instance()->flush();}
/*format,...形式是可变参数,一种格式化输入的表达
宏的作用是替换,也就是把函数中遇到的所有LOG_INFO(format,...) 替换成后面的话,
也就是if不是函数表达式的判断,记住宏只会做替换,if语句是被替换的部分,如果m_close_log是0,就执行后面的write_log
所以非0时候的情况也显然了,就是跳过语句;
__VA_ARGS__:把前面的可变参数...里代表的东西搬过来
##,如果__VA_ARGS__里面有参数,就不动,如果没有参数,就把前面的','以除掉,保证语法正确.
fflush:刷新流中为输出的信息,避免下一次log的时候出现错误信息
*/
#define LOG_INFO(format, ...) if(0 == m_close_log) {Log::get_instance()->write_log(1, format, ##__VA_ARGS__); Log::get_instance()->flush();}
#define LOG_WARN(format, ...) if(0 == m_close_log) {Log::get_instance()->write_log(2, format, ##__VA_ARGS__); Log::get_instance()->flush();}
#define LOG_ERROR(format, ...) if(0 == m_close_log) {Log::get_instance()->write_log(3, format, ##__VA_ARGS__); Log::get_instance()->flush();}

#endif
