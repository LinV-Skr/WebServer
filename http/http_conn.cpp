#include "./http_conn.h"
#include "http_conn.h"

http_conn::http_conn()
{
    int a = 10;
}

http_conn::~http_conn() {}

void http_conn::InitUserInfoFromMysql(Mysql_Connection_Pool *mysql)
{
    MYSQL * t_mysql_conn = mysql->GetConnection();
    //  数据库查询
    int t_mysql_error = mysql_query(t_mysql_conn, "select * from user");
    //  结果保存
    MYSQL_RES * t_mysql_res = mysql_store_result(t_mysql_conn);
    while(MYSQL_ROW row = mysql_fetch_row(t_mysql_res))
    {
        if(nullptr == row[0] || nullptr == row[1])
        {
            continue;
        } 
        std::string t_str_user_name = row[0];
        std::string t_str_user_passwd = row[1];
        m_user[t_str_user_name] = t_str_user_passwd;
    }
}