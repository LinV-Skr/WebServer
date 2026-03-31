#ifndef HTTP_CONN_H
#define HTTP_CONN_H

#include "../mysql/sql_connection_pool.h"

#include <map>

class http_conn
{
public:
    //  构造函数
    http_conn();
    //  析构函数
    ~http_conn();
    //  根据数据库表，初始化当前用户名、密码
    void InitUserInfoFromMysql(Mysql_Connection_Pool * mysql_conn);
private:
    //  用户名，密码
    std::map<std::string, std::string> m_user;
};

#endif