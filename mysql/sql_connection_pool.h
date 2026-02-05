#ifndef SQL_CONNECTION_POOL_H
#define SQL_CONNECTION_POOL_H

#include<mysql/mysql.h>

#include"../config/config_contains.h"

class Mysql_Connection_Pool {
public:
    /**
     * 函数功能：构建数据库链接池单例
     * 返回值：数据库链接池单例
    */
    static Mysql_Connection_Pool * GetInstance();
    /**
     * 函数功能：初始化数据库链接池单例
    */
    void Init(const std::string url, const std::string userName, const std::string userPasswd, const std::string dataBaseName, const int port, const int maxConn, const LogStatus logStatus);
private:
    //  数据库链接地址
    std::string m_url;
    //  用户名
    std::string m_userName;
    //  用户密码
    std::string m_userPasswd;
    //  数据库名
    std::string m_dataBaseName;
    //  数据库链接端口
    int m_port;
    //  最大链接数量
    int m_maxConn;
    //  日志状态
    LogStatus m_logStatus;
    MYSQL * conn;
};

#endif