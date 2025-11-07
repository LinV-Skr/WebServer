#include "log.h"

Log::Log()
{
    m_count = 0;
    m_is_async = false;
}

Log::~Log()
{
    delete m_block_queue;
    m_block_queue = nullptr;
}

bool Log::Init(const char * file_name, int close_log, int log_buff_size, int split_lines, int max_queue_size)
{
    //  如果设置了max_queue_size，则设为异步
    if(1 <= max_queue_size)
    {
        m_is_async = true;
        m_block_queue = new BlockQueue<string>(max_queue_size);
        //  创建线程
        pthread_t tid;
        //  TODO: 线程回收
        //  TODO: 回调函数
        pthread_create(&tid, NULL, Flush_Log_Thread, NULL);
    }
    return true;
}