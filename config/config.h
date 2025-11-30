#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<fstream>
#include<stdexcept>
#include "./config_type.h"

using namespace std;

class Config
{
public:
    //  静态工厂方法，从配置文件加载
    static Config LoadFromFile(const string & path);

private:
    Config() = default;
    // json格式解析
    bool ParseFromJson(const string & path);

    //  端口号
    int m_port = 9006;
    //  日志写入方式
    LogWriteMode m_logWrite = LogWriteMode::Sync;
    //  触发组合模式
    TrigMode m_trigMode = TrigMode::Listen_fd;
    //  listenfd触发模式
    ListenTrigMode m_listenTrigMode = ListenTrigMode::LT;
    //  connfd触发模式
    ConnTrigMode m_connTrigMode = ConnTrigMode::LT;
    //  优雅关闭连接，0-不使用
    CloseMode m_closeMode = CloseMode::Immediate;
    //  数据库连接池数量
    int m_sqlNum = 8;
    //  线程池内线程数量
    int m_threadNum = 8;
    //  是否关闭日志，0-不关闭
    LogStatus m_closeLog = LogStatus::Open;
    //  并发模型选择，0-ProActor
    ActorModel m_actorModel = ActorModel::ProActor;
    //  数据库名
    string m_dbName = "webserver";
    //  数据库用户名
    string m_dbUserName = "root";
    //  数据库用户名密码
    string m_dbUserPasswd = "root";
};

#endif