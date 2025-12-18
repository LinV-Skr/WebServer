#include"./config/config.h"
#include"./WebServer/webserver.h"
#include<iostream>

int main(int argc, char * argv[])
{
    try {
        //  解析参数
        Config cfg = Config::LoadFromFile("/home/linv/LinPro/WebServer/config/config.json");
        
        //  webserver 初始化
        WebServer server;
        server.Init(cfg);
        
        //  日志 初始化
        server.LogWrite();

        //  数据库
    }
    catch(const std::exception & e) {
        std::cerr << "Config Error : " << e.what() << std::endl;
        return -1;
    }

    return 0;
}