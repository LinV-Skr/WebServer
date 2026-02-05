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
#include "../mysql/sql_connection_pool.h"

class WebServer
{
public:
    /**
     * 函数功能： 服务器类构造函数
    */
    WebServer();
    /**
     * 函数功能：服务器类析构函数
    */
    ~WebServer();
    /**
     * 函数功能：初始化服务器实体参数
     * 输入参数：config - 配置实体
    */
    void ParameterInit(const Config & config);
    /**
     * 函数功能：日志单例参数初始化
    */
    void LogWriteInit();
    /**
     * 函数功能：初始化数据库链接池
    */
    void SqlPoolInit();
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
    //  数据库连接池
    Mysql_Connection_Pool * m_mysql_conn_pool;
};

#endif