#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "../lock/locker.h"

#include "../CGImysql/sql_connection_pool.h" 

template <typename T>
/*线程池类型的变量都定义在这里面了
线程池最重要的就是共享资源锁的问题,其余部分的编写其实熟悉语言之后就可以实现
所以手写线程池似乎并不是一件不可能完成的事情?
*/
class threadpool
{
public:
    /*thread_number是线程池中线程的数量，max_requests是请求队列中最多允许的、等待处理的请求的数量*/
    threadpool(int actor_model, connection_pool *connPool, int thread_number = 8, int max_request = 10000);
    ~threadpool();
    bool append(T *request, int state);
    bool append_p(T *request);

private:
    /*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
    static void *worker(void *arg);
    void run();

private:
    int m_thread_number;        //线程池中的线程数
    int m_max_requests;         //请求队列中允许的最大请求数
    pthread_t *m_threads;       //描述线程池的数组，其大小为m_thread_number
    std::list<T *> m_workqueue; //请求队列
    locker m_queuelocker;       //保护请求队列的互斥锁
    //设置一个信号量m_queuestat
    sem m_queuestat;            //是否有任务需要处理
    connection_pool *m_connPool;  //数据库
    int m_actor_model;          //模型切换
};
//初始化
//构建函数,创造一个线程池类
template <typename T>
threadpool<T>::threadpool( int actor_model, connection_pool *connPool, int thread_number, int max_requests) : 
m_actor_model(actor_model),m_thread_number(thread_number), 
m_max_requests(max_requests), m_threads(NULL),m_connPool(connPool)
{   //如果线程数或者允许的最大请求数<=0,参数设置有问题,报错
    if (thread_number <= 0 || max_requests <= 0)
        throw std::exception();
    //申请m_thread_number个线程空间,用指针进行管理
    //new 在堆区申请一片内存,有两种使用场景1.希望开辟比较大的一部分内存空间存储(栈空间较小)
    //2.希望手动释放遍量而不是随着程序运行结束而终止生命.
    m_threads = new pthread_t[m_thread_number];
    if (!m_threads)
        throw std::exception();
    for (int i = 0; i < thread_number; ++i)
    {
        /*pthread_create: m_threads+i 线程存储的地址空间
        第二个参数不重要. worker,线程的工作程序. 
        第四个参数:worker传递的参数,this表示把实例自己传进去
        类似python中的self.
        */
        if (pthread_create(m_threads + i, NULL, worker, this) != 0)
        {//如果返回值非0,说明有错误,删除线程并且抛出一个错误
            delete[] m_threads;
            throw std::exception();
        }/*将第i个线程状态设置为unjoinable. 若不设置,默认为joinable,线程终止
        需要主线程通过join函数回收资源(而join函数阻塞).如果是unjoinable,则线程
        运行结束自动释放资源.
        */
        if (pthread_detach(m_threads[i]))
        {//如果返回值是0,说明有错误,删除线程并且抛出一个错误
            delete[] m_threads;
            throw std::exception();
        }
    }
}
template <typename T>
threadpool<T>::~threadpool()
{   //析构函数,释放申请的线程空间.
    delete[] m_threads;
}
template <typename T>
bool threadpool<T>::append(T *request, int state)
{
    m_queuelocker.lock();
    if (m_workqueue.size() >= m_max_requests)
    {
        m_queuelocker.unlock();
        return false;
    }
    request->m_state = state;//要传进去状态,读还是写
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    //队列中添加请求后,如果没有挂起线程,信号量+1,如果有挂起线程,唤醒之
    m_queuestat.post();
    return true;
}
template <typename T>
//append_p: 在保证数据安全的情况下将请求加入请求队列
bool threadpool<T>::append_p(T *request)
{
    //请求队列属于共享资源,对队列中添加/删除请求的时候都务必要上锁
    m_queuelocker.lock();
    if (m_workqueue.size() >= m_max_requests)//工作队列请求达到上限了,解锁,返回错误
    {
        m_queuelocker.unlock();
        return false;
    }//相比于append,append_p不需要传读或者写的状态了,因为主线程已经做好了
    m_workqueue.push_back(request);//将请求加入工作队列
    m_queuelocker.unlock();
    m_queuestat.post();//队列中添加请求后,信号量+1,同步消息给工作线程
    return true;
}
template <typename T>
//返回一个指针类型变量;传进来的也是一个指针变量
void *threadpool<T>::worker(void *arg)
{   //把传递进来的指针强转成threadpool*类型
    threadpool *pool = (threadpool *)arg;
    //执行这个类中个run函数,返回这个指针
    pool->run();
    return pool;
}
//工作线程运行的主要工作逻辑
//工作线程就一直在这个run工作循环
template <typename T>
void threadpool<T>::run()
{
    while (true)
    {
        /*m_queuestat:用来判断请求能否被满足的锁.
        信号量-1,如果小于0挂起等待
        m_queuestat为了确保请求队列里由请求再让线程操作
        而m_queuelocker是为了确保只有一个线程在取请求队列的请求(因为
        涉及到出队操作),这两个机制保证的是不同的事情.
        */
        m_queuestat.wait();//查询请求队列中是否有可用执行请求
        m_queuelocker.lock();//查询请求队列是否正在被访问,访问共享资源解锁
        //这句话我感觉没有必要,因为wait()已经保证了工作队列不为空了,这里可以看成是以防万一
        if (m_workqueue.empty()) 
        {
            m_queuelocker.unlock();
            continue;
        }//取出第一个请求
        T *request = m_workqueue.front(); //首元素
        m_workqueue.pop_front();//取请求
        //取完请求之后,可以释放锁让其他线程继续取请求了
        m_queuelocker.unlock();
        if (!request)
            continue;
        //上述是处理共享资源的部分,下面是业务逻辑的部分

        //1是reactore模式,工作线程要处理读写请求
        if (1 == m_actor_model)
        {
            if (0 == request->m_state)
            {       //一次性把http报文全部读取出来
                if (request->read_once())
                {   //这里improv是啥意思
                    request->improv = 1;
                    connectionRAII mysqlcon(&request->mysql, m_connPool);
                    request->process();
                }
                else
                {
                    request->improv = 1;
                    request->timer_flag = 1;
                }
            }
            else
            {
                if (request->write())
                {
                    request->improv = 1;
                }
                else
                {
                    request->improv = 1;
                    request->timer_flag = 1;
                }
            }
        }
        else
        {   /*0是模拟proactor模式,读写请求在主线程处理,工作线程
            只需要处理业务逻辑; 与数据库建立连接; &request->mysql是一个传出参数;
            通过修改mysql值来使得request获得数据库连接;
            */
            connectionRAII mysqlcon(&request->mysql, m_connPool);
            request->process();//rquest是个http_conn类型的数据
            //进程结束,自动调用了mysqlcon的析构函数
        }
    }
}
#endif
