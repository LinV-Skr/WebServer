#include"./config/config.h"
#include"./WebServer/webserver.h"
#include<iostream>

int main(int argc, char * argv[])
{
    //  解析程序运行时的输入参数
    try {
        Config cfg = Config::LoadFromFile("/home/linv/LinPro/WebServer/config/config.json");
    }
    catch(const std::exception & e) {
        std::cerr << "Config Error : " << e.what() << std::endl;
        return -1;
    }
    

    //  webserver 初始化
    //WebServer server;
    //server.Init();
    
    //  日志
    //server.LogWrite();

    //  数据库
    
    return 0;
}