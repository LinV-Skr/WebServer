#include "log.h"

Log::Log()
{
    m_count = 0;
    m_is_async = false;
    m_block_queue = nullptr;
    m_fp = nullptr;
}

Log::~Log()
{
    delete m_block_queue;
    m_block_queue = nullptr;

    if(nullptr != m_fp)
    {
        fclose(m_fp);
        delete m_fp;
        m_fp = nullptr;
    }
}

bool Log::Init(const char * file_name, int close_log, int log_buf_size, int split_lines, int max_queue_size)
{
    //  如果设置了max_queue_size，则设为异步
    if(1 <= max_queue_size)
    {
        m_is_async = true;
        m_block_queue = new BlockQueue<string>(max_queue_size);
        //  创建线程
        pthread_t tid;
        //  TODO: 线程回收
        pthread_create(&tid, NULL, Flush_Log_Thread, NULL);
    }

    m_close_log = close_log;
    m_log_buff_size = log_buf_size;
    m_log_buf = new char[log_buf_size];
    memset(m_log_buf, '\0', m_log_buff_size);
    m_split_lines = split_lines;

    time_t t_time = time(NULL);
    struct tm t_tm;
    //  localtime函数存在线程安全问题
    localtime_r(&t_time, &t_tm);

    const char * p_file_name = strrchr(file_name, '/');
    char log_file_name[256] = {0};
    if(NULL == p_file_name)
    {
        snprintf(log_file_name, 255, "%d_%2d_%2d_%s", t_tm.tm_year + 1900, t_tm.tm_mon, t_tm.tm_mday, file_name);
    }

    return true;
}