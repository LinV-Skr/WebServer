#include "config.h"
#include<nlohmann/json.hpp>

using json = nlohmann::json;

Config Config::LoadFromFile(const string & config_path)
{
    Config cfg;
    bool res = cfg.ParseFromJson(config_path);
    if(false == res)
        throw runtime_error("File Open Error");

    

    return cfg;
}

bool Config::ParseFromJson(const string & config_path) {
    //  json文件读入stream流
    ifstream file(config_path);
    if(!file.is_open()) 
        return false;
    
    //  json 解析
    json j;
    file >> j;
    
    //  端口
    m_port = j.value("port", 9007);
    //  日志写入模式
    string logWrite_str = j.value("LogWriteMode", "Sync");
    if("Sync" == logWrite_str) 
        m_logWrite = LogWriteMode::Sync;
    else if("Async" == logWrite_str)
        m_logWrite = LogWriteMode::Async;
    //  触发组合模式
    string trigMode_str = j.value("TrigMode", "Listen_fd");
    if("Listen_fd" == trigMode_str)
        m_trigMode = TrigMode::Listen_fd;
    //  listen_fd触发模式
    string listenTrigMode_str = j.value("ListenTrigMode", "LT");
    if("LT" == listenTrigMode_str)
        m_listenTrigMode = ListenTrigMode::LT;
    //  connfd触发模式
    string connTrigMode_str = j.value("ConnTrigMode", "LT");
    if("LT" == connTrigMode_str)
        m_connTrigMode = ConnTrigMode::LT;
    //  

    

    return true;
}