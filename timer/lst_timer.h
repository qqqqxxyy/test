#ifndef LST_TIMER
#define LST_TIMER

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/uio.h>

#include <time.h>
#include "../log/log.h"

//这个头文件里面主要有两个类型:sort_timer_lst 和 Utils
//sort_timer_lst用来创建和维护一个定时器链表
//Utils用来封装对于内核事件表的操作,同时 Utils里面也封装有sort_timer_lst用来管理和调用之

class util_timer;
//用户结构,描述用户信息
//将客户端信息和定时器和通信地址封装在一起
//封装sockfd是为了更新链表(当某个fd请求发生之后,寻找并将其放到队尾)
//封装address是为了处理不活跃连接
//封装定时器是为了判断其是否超时.
struct client_data
{
    sockaddr_in address; //客户端sock连接地址
    int sockfd; //和客户端通信的文件描述符
    util_timer *timer; //定时器
};

//一个定时器节点类
class util_timer
{
public:
    //类实例化函数,将prev和next指针制为0
    util_timer() : prev(NULL), next(NULL) {}

public:
    //记录时间
    time_t expire;
    //这里定义了一个函数指针
    void (* cb_func)(client_data *);
    //用户数据
    client_data *user_data;
    //定时器双链表要有其前趋和后继
    util_timer *prev;
    util_timer *next;
};

//定时器链表，它是一个升序，双向链表，且带有头节点和尾节点
//链表中每一个节点都是一个定时器类类型
class sort_timer_lst
{
public:
    sort_timer_lst();
    ~sort_timer_lst();
    //向链表中增加一个定时器
    void add_timer(util_timer *timer);
    //调整链表中某个定时器
    void adjust_timer(util_timer *timer);
    //删除某个定时器
    void del_timer(util_timer *timer);
    //定时器时间+1
    void tick();

private:
    void add_timer(util_timer *timer, util_timer *lst_head);

    util_timer *head;
    util_timer *tail;
};

//工具类,把一些操作封装在这里面
class Utils
{
public:
    //构造和析构都不执行任何操作
    Utils() {}
    ~Utils() {}
    //timeslot超时单位
    void init(int timeslot);

    //对文件描述符设置非阻塞
    int setnonblocking(int fd);

    //将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
    //在listen和loop中被调用,和定时器链表无关
    void addfd(int epollfd, int fd, bool one_shot, int TRIGMode);

    //信号处理函数
    static void sig_handler(int sig);

    //设置信号函数
    void addsig(int sig, void(handler)(int), bool restart = true);

    //定时处理任务，重新定时以不断触发SIGALRM信号
    void timer_handler();

    void show_error(int connfd, const char *info);

public:
    static int *u_pipefd;
    sort_timer_lst m_timer_lst;
    static int u_epollfd;
    int m_TIMESLOT;
};

void cb_func(client_data *user_data);

#endif
