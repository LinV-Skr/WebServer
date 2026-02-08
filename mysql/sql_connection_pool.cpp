#include"sql_connection_pool.h"

Mysql_Connection_Pool *Mysql_Connection_Pool::GetInstance() {
    static Mysql_Connection_Pool  instance;
    return &instance;
}

void Mysql_Connection_Pool::Init(const std::string url, const std::string userName, 
    const std::string userPasswd, const std::string dataBaseName, const int port, 
    const int maxConn, const LogStatus logStatus) {
    //  成员变量初始化
    m_url = url;
    m_userName = userName;
    m_userPasswd = userPasswd;
    m_dataBaseName = dataBaseName;
    m_port = port;
    m_maxConn = maxConn;
    m_logStatus = logStatus;

    LOG_ERROR("MysqlConnError");

    //  根据输入参数，链接数据库
    for(int i = 0; i < m_maxConn; i++) {
        //  数据库链接句柄初始化
        MYSQL * conn = NULL;
        conn = mysql_init(conn);
        //  安全检查 - 初始化失败
        if(NULL == conn) {
            LOG_ERROR("MysqlConnError");
            throw 
        }
        //  数据库连接
        conn = mysql_real_connect(conn, url.c_str(), userName.c_str(), userPasswd.c_str(), dataBaseName.c_str(), port, NULL, 0);
        if(NULL == conn) {

        }
        //  链接成功后，更新链接池
    }
}
