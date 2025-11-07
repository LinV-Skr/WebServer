#ifndef LOG_H
#define LOG_H

#include <string>
#include <pthread.h>

#include "./block_queue.h"

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
    void * Flush_Log_Thread(void * arg)
    {
        return nullptr;
    }

    //  初始化函数
    bool Init(const char * file_name, int close_log, int log_buff_size = 8192,
                int split_lines = 5000000, int max_queue_size = 0);

private:
    //  日志行数记录
    long long m_count;

    //  是否同步标志位
    bool m_is_async;

    //  日志阻塞队列
    BlockQueue<string> * m_block_queue;
};

#endif