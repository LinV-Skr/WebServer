#ifndef CONFIG_TYPE_H
#define CONFIG_TYPE_H

enum class LogWriteMode
{
    Sync,
    Async
};

enum class TrigMode
{
    Listen_fd,
    Conn_fd
};

enum class ListenTrigMode
{
    LT
};

enum class ConnTrigMode
{
    LT
};

enum class CloseMode
{
    GraceFul,
    Immediate
};

enum class LogStatus
{
    Open,
    Close
};

enum class ActorModel
{
    ProActor
};

#endif