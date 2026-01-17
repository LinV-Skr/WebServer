#include"./config/config.h"
#include"./WebServer/webserver.h"
#include<iostream>

int main(int argc, char * argv[]) {
    try {
        //  解析、加载配置文件
        Config cfg = Config::LoadFromFile(config_file_path);
        //  加载WebServer
        WebServer server;
        //  初始化WebServer参数
        server.ParameterInit(cfg);
        //  日志初始化
        server.LogWriteInit();
        //  初始化数据库
        
    }
    catch(const std::exception & e) {
        std::cerr << "Config Error : " << e.what() << std::endl;
        return -1;
    }
    return 0;
}