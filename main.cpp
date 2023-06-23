#include "config.h"

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "1231";
    string databasename = "yourdb";

    //实例化参数解析类,同时实例化函数中包含了对于变量的初始化
    Config config; //在config.h中定义
    //传递的是:./server [-p port] [-l LOGWrite] [-m TRIGMode] [-o OPT_LINGER]
    // [-s sql_num] [-t thread_num] [-c close_log] [-a actor_model]
    //功能类比于python的argparser即可
    config.parse_arg(argc, argv);
    //实例化webserver,首先调用的是构造函数
    WebServer server;//在webserver.h中定义

    //初始化
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

    /*前面四个函数log_write(),sql_pool(),thread_pool(),trig_mode()只涉及相关功能初始化的部分
    后面两个函数 eventListen , eventLoop 才是真正主线程执行的代码.
    */
    /*日志和数据库连接池都是单例模式类,保证资源的同步
    */
    //日志
    //通过Log::get_instance()获得唯一的日志类实例
    server.log_write();

    //数据库
    server.sql_pool();

    //初始化线程池
    server.thread_pool();

    //触发模式
    server.trig_mode();

    /*监听事件
    主要完成:创建监听套接字,创建监听信号的匿名管道,
    在内核注册epoll事件表,在事件表中添加监听套接字和匿名管道对应的文件描述符
    */
    server.eventListen();

    //运行,循环接受事件
    server.eventLoop();

    return 0;
}