#include "config.h"

//  test
#include<iostream>
#include<cerrno>
#include<cstring>

Config Config::LoadFromFile(const string & config_path)
{
    Config cfg;
    bool res = cfg.ParseFromJson(config_path);
    if(false == res)
        throw runtime_error("File Open Error");
    return cfg;
}

bool Config::ParseFromJson(const string & config_path) {
    ifstream file(config_path);
    if(!file.is_open()) {
        std::cerr << "错误码: " << errno << " (" << strerror(errno) << ")" << std::endl;
        return false;
    }
    return true;
}