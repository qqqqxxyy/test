#include "config.h"
//储存输入端输入的一些信息
/*包括port,logwrite,trigmode,listentrigmode,connttrigmode,
    opt_linfer //啥叫优雅关闭链接,应该就是说让程序在析构的时候主动关闭链接的意思吧?
    sql_num,thread_num,close_log,actor_model
这两段代码只要照着抄就好了,因为规程化比较严重,无非是一些从命令行读取参数,想加就多加一行
有的不想要就删除一行.
*/
Config::Config(){
    //端口号,默认9006
    PORT = 9006;

    //日志写入方式，默认同步
    //0同步写入,1异步写入
    //选择会被webserver类中的m_log_write变量所记录
    LOGWrite = 0;

    //触发组合模式,默认listenfd LT + connfd LT
    TRIGMode = 0;

    //listenfd触发模式，默认LT
    LISTENTrigmode = 0;

    //connfd触发模式，默认LT
    CONNTrigmode = 0;

    //优雅关闭链接，默认不使用
    OPT_LINGER = 0;

    //数据库连接池数量,默认8
    sql_num = 8;

    //线程池内的线程数量,默认8
    thread_num = 8;

    //关闭日志,默认不关闭
    close_log = 0;

    //并发模型,默认是模拟proactor
    actor_model = 0;
}

void Config::parse_arg(int argc, char*argv[]){
    int opt;
    //这表示每个表示符后面的合法语法都是跟空格
    const char *str = "p:l:m:o:s:t:c:a:";
    //自动按照str集解析argv中的相关参数
    /*这里optarg是预先定义在其他地方了,并且在unistd.h中被extern语句声明过
    */
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'p':
        {
            PORT = atoi(optarg);
            break;
        }
        case 'l':
        {
            LOGWrite = atoi(optarg);
            break;
        }
        case 'm':
        {
            TRIGMode = atoi(optarg);
            break;
        }
        case 'o':
        {
            OPT_LINGER = atoi(optarg);
            break;
        }
        case 's':
        {
            sql_num = atoi(optarg);
            break;
        }
        case 't':
        {
            thread_num = atoi(optarg);
            break;
        }
        case 'c':
        {
            close_log = atoi(optarg);
            break;
        }
        case 'a':
        {
            actor_model = atoi(optarg);
            break;
        }
        default:
            break;
        }
    }
}