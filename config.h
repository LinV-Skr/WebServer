#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

class Config
{
public:
    Config();
    ~Config(){};

    //  解析程序运行时的输入参数
    void ParseArg(int argc, char * argv[]);

public:
    //  端口号
    int m_port;

    //  日志写入方式
    int m_logWrite;

    //  触发组合模式
    int m_trigMode;

    //  listenfd触发模式
    int m_listenTrigMode;

    //  connfd触发模式
    int m_connTrigMode;

    //  优雅关闭连接
    int m_optLinger;

    //  数据库连接池数量
    int m_sqlNum;

    //  线程池内线程数量
    int m_threadNum;
    
    //  是否关闭日志
    int m_closeLog;

    //  并发模型选择
    int m_actorModel;
};

#endif