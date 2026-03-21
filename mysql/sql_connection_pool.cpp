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

    //  根据输入参数，链接数据库
    for(int i = 0; i < m_maxConn; i++) {
        //  数据库链接句柄初始化
        MYSQL * conn = NULL;
        conn = mysql_init(conn);
        //  安全检查 - 初始化失败
        if(NULL == conn) {
            LOG_ERROR("MySQL_Init_Error");
            throw runtime_error("MySQL_Init_Error");
        }
        //  数据库连接
        conn = mysql_real_connect(conn, 
                            "127.0.0.1", // 主机名
                            "root",      // 用户名
                            "WebServer12345@@",  // 密码
                            "WebServer",   // 默认数据库
                            0,           // 端口 (0表示默认3306)
                            NULL,        // unix_socket
                            0);
        
        if(NULL == conn) {
            printf("MySQL Connect Error : %s\n", mysql_error(conn));
            unsigned int err_no = mysql_errno(conn);
            LOG_ERROR("MySQL_Connect_Error");
            throw runtime_error("MySQL_Connect_Error");
        }
        //  链接成功后，更新链接池
        m_free_conn_num++;
        m_conn_list.push_back(conn);
    }

    m_sem_emptyLink = sem(m_free_conn_num);
}

MYSQL * Mysql_Connection_Pool::GetConnection() {
    if(0 == m_conn_list.size()) {
        return NULL;
    }

    m_sem_emptyLink.wait();
    m_lock.lock();
    MYSQL * res = m_conn_list.front();
    m_conn_list.pop_front();
    m_free_conn_num--;
    m_lock.unlock();

    return res;
}