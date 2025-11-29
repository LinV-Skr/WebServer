#include "./config/config.h"
#include "./WebServer/webserver.h"

int main(int argc, char * argv[])
{
    //  解析程序运行时的输入参数
    Config cfg = Config::LoadFromFile("./config/config.json");

    //  webserver 初始化
    //WebServer server;
    //server.Init();
    
    //  日志
    //server.LogWrite();

    //  数据库
    
    return 0;
}