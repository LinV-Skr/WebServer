#ifndef WEBSERVER_H
#define WEBSERVER_H

#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<vector>

#include "../http/http_conn.h"
#include "../timer/lst_timer.h"
#include "../log/log.h"
#include "../config/config.h"

class WebServer
{
public:
    WebServer();
    ~WebServer();

public:
    void Init(const Config& config);
    void LogWrite();
    void SqlPool();

public:
    //  端口号
    int m_port;

    //  日志写入方式
    LogWriteMode m_logWrite;

    //  优雅关闭连接
    CloseMode m_closeMode;

    //  触发模式
    TrigMode m_trigMode;

    //  数据库链接数目
    int m_sqlNum;

    //  线程池数目
    int m_threadNum;

    //  是否关闭日志
    LogStatus m_logStatus;

    //  并发模型
    ActorModel m_actor_mode;

    //  数据库
    string m_database_user;
    string m_database_passwd;
    string m_database_name;

    //  http连接用户
    http_conn * m_users;

    //  webserver的root工作目录
    string m_root_path;

    //  定时器相关
    client_data * m_users_timer;
};

#endif