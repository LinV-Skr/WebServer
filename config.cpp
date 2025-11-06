#include "config.h"

//  构造函数
Config::Config()
{
    //  端口号，默认9006
    m_port = 9006;

    //  日志写入方式，默认同步
    m_logWrite = 0;

    //  触发组合模式，默认listenfd LT + connfd LT
    m_trigMode = 0;

    //  listenfd触发模式，默认LT
    m_listenTrigMode = 0;

    //  connfd触发模式，默认LT
    m_connTrigMode = 0;

    //  优雅关闭连接，默认不适用
    m_optLinger = 0;

    //  数据库连接池数量，默认8
    m_sqlNum = 8;

    //  线程池内线程数量，默认是8
    m_threadNum = 8;

    //  关闭日志，默认不关闭
    m_closeLog = 0;

    //  并发模型，默认是ProActor
    m_actorModel = 0;
}

//  执行参数解析
void Config::ParseArg(int argc, char * argv[])
{
    int opt;
    const char * str = "p:l:m:o:s:t:c:a:";
    while((opt = getopt(argc, argv, str)) != -1)
    {
        switch(opt)
        {
            case 'p':
                m_port = atoi(optarg);
                break;
            case 'l':
                m_logWrite = atoi(optarg);
                break;
            case 'm':
                m_trigMode = atoi(optarg);
                break;
            case 'o':
                m_optLinger = atoi(optarg);
                break;
            case 's':
                m_sqlNum = atoi(optarg);
                break;
            case 't':
                m_threadNum = atoi(optarg);
                break;
            case 'c':
                m_closeLog = atoi(optarg);
                break;
            case 'a':
                m_actorModel = atoi(optarg);
                break;
            default:
                break;
        }
    }
}