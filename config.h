//如果没有定义过CONFIG_H,则在此处定义这个包,避免包的冲突
//从来没遇到过冲突的情况,不过写头文件的时候都会加上这句话
#ifndef CONFIG_H
#define CONFIG_H

#include "webserver.h"

using namespace std;

//虽然这里面只有一个config类,但是因为include "webserver.h"了,
//可以通过config.h加载webserver类
class Config
{
public:
    Config();//构造函数,变量初始化为默认值
    ~Config(){};//析构函数,不用定义可以有默认定义的?

    //实际上意思是接受命令行传来的参数,第一个是传来的参数个数,
    //第二个是传来的具体参数(字符串数组,长度就是传来参数的个数)
    void parse_arg(int argc, char*argv[]);//从命令行读取参数,初始化

    //端口号
    int PORT;

    //日志写入方式
    int LOGWrite;

    //触发组合模式
    int TRIGMode;

    //listenfd触发模式
    int LISTENTrigmode;

    //connfd触发模式
    int CONNTrigmode;

    //优雅关闭链接
    int OPT_LINGER;

    //数据库连接池数量
    int sql_num;

    //线程池内的线程数量
    int thread_num;

    //是否关闭日志
    int close_log;

    //并发模型选择
    int actor_model;
};

#endif