#include "webserver.h"

WebServer::WebServer()
{
    m_users = new http_conn[MAX_FD];
    
    //  root文件夹路径
    char server_path[200];
    getcwd(server_path, 200);
    char root_path[6] = "\root";
    m_root_path = (char *)malloc(strlen(server_path) + strlen(root_path) + 1);
    strcpy(m_root_path, server_path);
    strcat(m_root_path, root_path);

    //  定时器
    m_users_timer = new client_data[MAX_FD];
}

//  指针释放后，指控防止垂悬，防止双重释放
WebServer::~WebServer()
{
    delete [] m_users;
    m_users = nullptr;
    free(m_root_path);
    m_root_path = nullptr;
    delete [] m_users_timer;
    m_users_timer = nullptr;
}

void WebServer::Init(int port, string user, string passwd, string databaseName, int logWrite, 
                int optLinger, int trigMode, int sqlNum, int threadNum, int closeLog, int actorModel)
{
    m_port = port;
    m_database_user = user;
    m_database_passwd = passwd;
    m_database_name = databaseName;
    m_logWrite = logWrite;
    m_optLinger = optLinger;
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
    }
}