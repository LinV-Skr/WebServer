#ifndef CONFIG_CONTAINS_H
#define CONFIG_CONTAINS_H

#include<string>

//  最大文件描述符
const int MAX_FD = 65535;
const std::string config_file_path = "/home/linv/LinPro/WebServer/config/config.json";

enum class LogWriteMode {
    Sync,
    Async
};

enum class TrigMode {
    Listen_fd,
    Conn_fd
};

enum class ListenTrigMode {
    LT
};

enum class ConnTrigMode {
    LT
};

enum class CloseMode
{
    GraceFul,
    Immediate
};

enum class LogStatus {
    Open,
    Close
};

enum class ActorModel
{
    ProActor
};

#endif