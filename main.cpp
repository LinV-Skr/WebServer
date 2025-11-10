#include "config.h"
#include "webserver.h"

int main(int argc, char * argv[])
{
    //  需要修改的数据库信息，登录名，密码，库名
    string user = "root";
    string passwd = "root";
    string dataBase_name = "qgydb";

    //  解析程序运行时的输入参数
    Config config;
    config.ParseArg(argc, argv);

    //  webserver 初始化
    WebServer server;
    server.Init(config.m_port, user, passwd, dataBase_name, config.m_logWrite, config.m_optLinger, config.m_trigMode, config.m_sqlNum, 
                    config.m_threadNum, config.m_closeLog, config.m_actorModel);
    
    //  日志
    server.LogWrite();

    //  数据库
    
}