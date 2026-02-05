#ifndef CONFIG_H
#define CONFIG_H

#include<fstream>
#include<stdexcept>

#include "./config_contains.h"

using namespace std;

class Config {
public:
    /**
     * 函数功能：构建Config单例
     * 输入参数：config_file_path，配置文件路径
     * 返回值：Config单例
    */
    static Config LoadFromFile(const string & config_file_path);
    /**
     * 函数功能：获取服务器连接端口
     * 返回值：服务器连接端口
    */
    int GetServerPort() const;
    /**
     * 函数功能：获取数据库用户名
     * 返回值：数据库用户名
    */
    string GetDataBaseUserName() const;
    /**
     * 函数功能：获取用户名密码
     * 返回值：用户名密码
    */
    string GetDataBaseUserPwd() const;
    /**
     * 函数功能：获取数据库名称
     * 返回值：数据库名称
    */
    string GetDataBaseName() const;
    /**
     * 函数功能：获取日志谢日方式
     * 返回值：日志写入方式
    */
    LogWriteMode GetLogWriteMode() const;
    /**
     * 函数功能：获取服务器链接关闭方式
     * 返回值：服务器链接关闭方式
    */
    CloseMode GetCloseMode() const;
    /**
     * TODO - TrigMode添加注释
    */
    TrigMode GetTrigMode() const;
    /**
     * 函数功能：获取数据库链接池 - 链接数量
     * 返回值：数据库链接池 - 链接数量
    */
    int GetSqlPoolConnNum() const;
    /**
     * 函数功能：获取线程池 - 线程数量
     * 返回值：线程池 - 线程数量
    */
    int GetThreadPoolThreadNum() const;
    /**
     * 函数功能：获取日志状态
     * 返回值：日志状态
    */
    LogStatus GetLogStatus() const;
    /**
     * TODO - ActorModel添加注释
    */
    ActorModel GetActorModel() const;
private:
    /**
     * 函数功能：默认构造函数
    */
    Config() = default;
    /**
     * 函数功能：解析Json配置文件，并加载到Config实例
     * 输入参数：config_file_path，配置文件路径
     * 返回值：解析并加载成功返回true，否则返回false
    */
    bool ParseFromJson(const string & config_file_path);
    /**
     * 函数功能：检验Json配置文件中参数是否有效
     * 返回值：失败抛出异常
    */
    void Validate();
private:
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
    int m_sqlPool_connNum = 8;
    //  线程池内线程数量
    int m_threadPool_threadNum = 8;
    //  是否关闭日志，0-不关闭
    LogStatus m_logStatus = LogStatus::Open;
    //  并发模型选择，0-ProActor
    ActorModel m_actorModel = ActorModel::ProActor;
    //  数据库名
    string m_dbName = "WebServer";
    //  数据库用户名
    string m_dbUserName = "root";
    //  数据库用户名密码
    string m_dbUserPasswd = "root";
};

#endif