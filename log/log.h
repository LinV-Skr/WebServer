#ifndef LOG_H
#define LOG_H

#include<string.h>
#include<cstring>
#include<pthread.h>
#include<stdio.h>
#include<stdarg.h>

#include"./block_queue.h"
#include"../config/config.h"

using namespace std;

class Log {
public:
    /**
     * 函数功能：构建日志类实例
     * 返回值：日志实例
    */
    static Log & GetInstance();

    /**
     * 函数功能：异步线程读取阻塞队列中的日志，并写入日志文件
     * 输入参数：arg - 线程创建函数要求，尚未使用
    */
    static void * Flush_Log_Thread(void * arg);

    /**
     * 函数功能：日志单例初始化
     * 输入参数：file_name - 文件名全称，log_status - 日志状态，log_buff_size - 日志缓冲区大小，log_max_lines - 最大行数，
    */
    bool Init(string file_name, LogStatus log_status, int log_buff_size, int log_max_lines, int max_queue_size, LogWriteMode logWriteMode);

    /**
     * 函数功能：获取日志当前状态
     * 返回值：日志状态
    */
    LogStatus GetLogStatus() const;

    /**
     * 函数功能：日志缓冲区添加日志
     * 输入参数：level - 日志等级， format - 写入内容
    */
    void WriteLog(int level, const char * format, ...);

private:
    /**
     * 函数功能：日志单例 - 构造函数
    */
    Log();

    /**
     * 函数功能：日志单例 - 析构函数
    */
    ~Log();

    /**
     * 函数功能：日志异步携程写日志
    */
    void Async_Write_Log();

private:
    //  日志目录名
    string m_dirPath;
    //  日志文件名
    string m_logFileName;
    //  日志行数记录
    long long m_line_count;
    //  是否同步标志位
    bool m_isAsync = false;
    //  日志阻塞队列
    BlockQueue<string> * m_block_queue;
    //  互斥量
    locker m_mutex;
    //  日志文件
    FILE * m_fp;
    //  是否关闭日志
    LogStatus m_log_status = LogStatus::Open;
    //  日志缓冲区大小
    int m_log_buff_size;
    //  日志缓冲区
    char * m_log_buff;
    //  日志最大行数
    int m_log_max_lines = 0;
    //  日志按天分类，记录当前是哪一天
    int m_today;
};

#define LOG_DEBUG(format,...) do{ if(LogStatus::Open == Log::GetInstance().GetLogStatus())  Log::GetInstance().WriteLog(0, format, ##__VA_ARGS__); } while(0);
#define LOG_INFO(format,...) do{ if(LogStatus::Open == Log::GetInstance().GetLogStatus())  Log::GetInstance().WriteLog(1, format, ##__VA_ARGS__); } while(0);
#define LOG_WARN(format,...) do{ if(LogStatus::Open == Log::GetInstance().GetLogStatus())  Log::GetInstance().WriteLog(2, format, ##__VA_ARGS__); } while(0);
#define LOG_ERROR(format,...) do{ if(LogStatus::Open == Log::GetInstance().GetLogStatus())  Log::GetInstance().WriteLog(3, format, ##__VA_ARGS__); } while(0);

#endif