#include "webserver.h"

WebServer::WebServer() {
}

//  指针释放后，指控防止垂悬，防止双重释放
WebServer::~WebServer() {
    
}

void WebServer::ParameterInit(const Config & config) {
    m_port = config.GetServerPort();
    m_database_user = config.GetDataBaseUserName();
    m_database_passwd = config.GetDataBaseUserPwd();
    m_database_name = config.GetDataBaseName();
    m_logWrite = config.GetLogWriteMode();
    m_closeMode = config.GetCloseMode();
    m_trigMode = config.GetTrigMode();
    m_sqlNum = config.GetSqlPoolConnNum();
    m_threadNum = config.GetThreadPoolThreadNum();
    m_logStatus = config.GetLogStatus();
    m_actor_mode = config.GetActorModel();
}

void WebServer::LogWriteInit() {
    if(LogStatus::Open == m_logStatus) {
        Log::GetInstance().Init("./ServerLog", m_logStatus, 2000, 800000, 800, m_logWrite);
    }
}

void WebServer::SqlPoolInit() {
    //  初始化数据库链接池
    m_mysql_conn_pool = Mysql_Connection_Pool::GetInstance();
    
}