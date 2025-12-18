#ifndef LOG_H
#define LOG_H

#include<string>
#include<cstring>
#include<pthread.h>
#include<stdio.h>

#include"./block_queue.h"
#include"../config/config.h"

using namespace std;

class Log
{
private:
    Log();
    ~Log();

public:
    //  全局访问点
    static Log & GetInstance()
    {
        static Log m_instance;
        return m_instance;
    }

    //  删除拷贝控制，禁止复制/赋值
    Log(const Log &) = delete;
    Log& operator=(const Log &) = delete;

    //  异步线程回调函数
    static void * Flush_Log_Thread(void * arg)
    {
        Log::GetInstance().Async_Write_Log();
    }

    //  初始化函数
    bool Init(string file_name, LogStatus close_log, int log_buff_size = 8192,
                int split_lines = 5000000, int max_queue_size = 0);

private:
    void Async_Write_Log()
    {
        string single_log;
        while(m_block_queue->Pop(single_log))
        {
            m_mutex.lock();
            if(nullptr != m_fp)
            {
                fputs(single_log.c_str(), m_fp);
            }
        }
    }

private:
    //  日志目录名
    string m_dirPath;
    //  日志文件名
    string m_logFileName;
    //  日志行数记录
    long long m_count;
    //  是否同步标志位
    bool m_isAsync = false;
    //  日志阻塞队列
    BlockQueue<string> * m_block_queue;
    //  互斥量
    locker m_mutex;
    //  日志文件
    FILE * m_fp;
    //  是否关闭日志
    int m_close_log;
    //  日志缓冲区大小
    int m_log_buff_size;
    //  日志缓冲区
    char * m_log_buf;
    //  日志最大行数
    int m_split_lines;
    //  日志按天分类，记录当前是哪一天
    int m_today;
};

#endif