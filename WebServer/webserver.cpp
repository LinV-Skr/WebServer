#include "webserver.h"

WebServer::WebServer()
{
    m_users = new http_conn[MAX_FD];
    
    //  在当前工作路径下，组装root路径
    //  获取当前工作路径
    size_t size = 256;
    vector<char> buffer(size);
    if(getcwd(buffer.data(), size) == NULL) {
        perror("getcwd error");
        exit(-1);
    }
    string work_path(buffer.data());
    m_root_path = work_path + "/root";

    //  定时器
    m_users_timer = new client_data[MAX_FD];
}

//  指针释放后，指控防止垂悬，防止双重释放
WebServer::~WebServer()
{
    delete [] m_users;
    m_users = nullptr;
    m_root_path = nullptr;
    delete [] m_users_timer;
    m_users_timer = nullptr;
}

void WebServer::Init(const Config & config)
{
    m_port = config.GetServerPort();
    m_database_user = config.GetDataBaseUserName();
    m_database_passwd = config.GetDataBaseUserPwd();
    m_database_name = config.GetDataBaseName();
    m_logWrite = config.GetLogWriteMode();
    m_closeMode = config.GetCloseMode();
    m_trigMode = config.GetTrigMode();
    m_sqlNum = config.GetSqlNum();
    m_threadNum = config.GetThreadNum();
    m_logStatus = config.GetLogStatus();
    m_actor_mode = config.GetActorModel();
}

void WebServer::LogWrite()
{
    if(LogStatus::Open == m_logStatus)
    {
        if(LogWriteMode::Async == m_logWrite)
            Log::GetInstance().Init("./ServerLog", m_logStatus, 2000, 800000, 800);
        else if(LogWriteMode::Sync == m_logWrite)
            Log::GetInstance().Init("./ServerLog", m_logStatus, 2000, 800000, 0);
    }
}

void WebServer::SqlPool()
{
    //  初始化数据库链接池
    
}