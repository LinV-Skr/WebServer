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
    m_trigMode = trigMode;
    m_sqlNum = sqlNum;
    m_threadNum = threadNum;
    m_close_log = closeLog;
    m_actor_mode = actorModel;
}

void WebServer::LogWrite()
{
    //  0 日志不关闭
    if(0 == m_close_log)
    {
        //  1  日志异步； 0  日志同步
        if(1 == m_logWrite)
            Log::GetInstance().Init("./ServerLog", m_close_log, 2000, 800000, 800);
        else
            Log::GetInstance().Init("./ServerLog", m_close_log, 2000, 800000, 0);
    }
}

void WebServer::SqlPool()
{
    //  初始化数据库链接池
    
}