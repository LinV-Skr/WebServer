#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "./http/http_conn.h"
#include "./timer/lst_timer.h"
#include "./log/log.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//  最大文件描述符
const int MAX_FD = 65535;

class WebServer
{
public:
    WebServer();
    ~WebServer();

public:
    void Init(int port, string user, string passwd, string databaseName, int logWrite, 
                int optLinger, int trigMode, int sqlNum, int threadNum, int closeLog, int actorModel);
    void LogWrite();

public:
    //  端口号
    int m_port;

    //  日志写入方式
    int m_logWrite;

    //  优雅关闭连接
    int m_optLinger;

    //  触发模式
    int m_trigMode;

    //  数据库链接数目
    int m_sqlNum;

    //  线程池数目
    int m_threadNum;

    //  是否关闭日志
    int m_close_log;

    //  并发模型
    int m_actor_mode;

    //  数据库
    string m_database_user;
    string m_database_passwd;
    string m_database_name;

    //  http连接用户
    http_conn * m_users;

    //  webserver的root工作目录
    char * m_root_path;

    //  定时器相关
    client_data * m_users_timer;
};

#endif