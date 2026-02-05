#include "config.h"
#include<nlohmann/json.hpp>

using json = nlohmann::json;

Config Config::LoadFromFile(const string & config_file_path) {
    static Config config_instance;
    static bool is_loaded = false;
    //  第一次构建单例时，加载配置
    if(!is_loaded) {
        //  解析失败
        bool res = config_instance.ParseFromJson(config_file_path);
        if(false == res) {
            throw runtime_error("File Parse Error");
        }
        //  检验参数
        config_instance.Validate();
    }
    return config_instance;
}

int Config::GetServerPort() const {
    return m_port;
}

string Config::GetDataBaseUserName() const {
    return m_dbUserName;
}

string Config::GetDataBaseUserPwd() const {
    return m_dbUserPasswd;
}

string Config::GetDataBaseName() const {
    return m_dbName;
}

LogWriteMode Config::GetLogWriteMode() const {
    return m_logWrite;
}

CloseMode Config::GetCloseMode() const {
    return m_closeMode;
}

TrigMode Config::GetTrigMode() const {
    return m_trigMode;
}

int Config::GetSqlPoolConnNum() const {
    return m_sqlPool_connNum;
}

int Config::GetThreadPoolThreadNum() const {
    return m_threadPool_threadNum;
}

LogStatus Config::GetLogStatus() const {
    return m_logStatus;
}

ActorModel Config::GetActorModel() const {
    return m_actorModel;
}

bool Config::ParseFromJson(const string & config_file_path) {
    //  打开json配置文件
    ifstream file(config_file_path);
    if(!file.is_open()) return false;

    //  初始化json对象
    json j;
    file >> j;

    //  解析 - 端口
    m_port = j.value("Port", 9007);
    //  解析 - 日志写入模式
    string logWrite_str = j.value("LogWriteMode", "Sync");
    if("Sync" == logWrite_str) m_logWrite = LogWriteMode::Sync;
    else if("Async" == logWrite_str) m_logWrite = LogWriteMode::Async;
    //  解析 - 触发组合模式
    string trigMode_str = j.value("TrigMode", "Listen_fd");
    if("Listen_fd" == trigMode_str) m_trigMode = TrigMode::Listen_fd;
    //  解析 - listen_fd触发模式
    string listenTrigMode_str = j.value("ListenTrigMode", "LT");
    if("LT" == listenTrigMode_str) m_listenTrigMode = ListenTrigMode::LT;
    //  解析 - connfd触发模式
    string connTrigMode_str = j.value("ConnTrigMode", "LT");
    if("LT" == connTrigMode_str) m_connTrigMode = ConnTrigMode::LT;
    //  解析 - 优雅关链接
    string closeMode_str = j.value("CloseMode", "Immediate");
    if("Immediate" == closeMode_str) m_closeMode = CloseMode::Immediate;
    else if("Graceful" == closeMode_str) m_closeMode == CloseMode::GraceFul;
    //  解析 - 数据库链接池数量
    int sqlThreadNum = j.value("SqlThreadNum", 8);
    m_sqlNum = sqlThreadNum;
    //  解析 - 线程池数量
    int threadNum = j.value("ThreadNum", 8);
    m_threadNum = threadNum;
    //  解析 - 日志是否打开
    string logStatus_str = j.value("LogStatus", "Open");
    if("Open" == logStatus_str) m_logStatus = LogStatus::Open;
    else if("Close" == logStatus_str) m_logStatus = LogStatus::Close;
    //  解析 - 并发模型
    string actorModel_str = j.value("ActorModel", "ProActor");
    if("ProActor" == actorModel_str) m_actorModel = ActorModel::ProActor;
    //  解析 - 数据库名称
    m_dbName = j.value("DataBaseName", "WebServer");
    //  解析 - 数据库用户名
    m_dbUserName = j.value("DataBaseUserName", "root");
    //  解析 - 数据库密码
    m_dbUserPasswd = j.value("DataBaseUserPwd", "root");

    //  结果返回
    return true;
}

void Config::Validate() {
    //  port检验
    if(m_port < 1 || m_port > 65535) throw invalid_argument("Port out of Range [1, 65535]");
    //  数据库链接池检验
    if(m_sqlNum < 1 || m_sqlNum > 100) throw invalid_argument("SqlThreadNum out of Range [1,100]");
    //  线程池检验
    if(m_threadNum < 1 || m_threadNum > 100) throw invalid_argument("ThreadNum out of Range [1,100]");
}

