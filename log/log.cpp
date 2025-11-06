#include "log.h"

Log::Log()
{
    m_count = 0;
    m_is_async = false;
}

Log::~Log()
{
    
}

bool Log::Init(const char * file_name, int close_log,
                int log_buff_size = 8, int split_lines = 5000000,
                int max_queue_size = 0)
{
    //  如果设置了max_queue_size，则设为异步
    if(1 <= max_queue_size)
    {
        m_is_async = true;
        
    }
}