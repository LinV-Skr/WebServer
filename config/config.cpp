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
    ifstream file(config_path);
    if(!file.is_open()) 
        return false;
    
    json j;
    file >> j;
    m_port = j.value("port", 9007);
    

    return true;
}