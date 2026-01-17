#include "log.h"

Log::Log() {
    m_count = 0;
    m_log_buff_size = 0;
    m_block_queue = nullptr;
    m_fp = nullptr;
    m_log_buf = nullptr;
}

Log::~Log() {
    delete m_block_queue;
    m_block_queue = nullptr;

    if(nullptr != m_fp)
    {
        fclose(m_fp);
        delete m_fp;
        m_fp = nullptr;
    }
}

bool Log::Init(string file_path, LogStatus log_status, int log_buf_size, int log_max_lines, int maxQueueSize, LogWriteMode logWriteMode) {
    //  异步写，创建线程、阻塞队列
    if(LogWriteMode::Async == logWriteMode) {
        m_isAsync = true;
        m_block_queue = new BlockQueue<string>(maxQueueSize);
        pthread_t tid;
        pthread_create(&tid, NULL, Flush_Log_Thread, NULL);
    }

    //  初始化日志参数
    log_status_ =  log_status;
    m_log_buff_size = log_buf_size;
    m_log_buf = new char[log_buf_size];
    memset(m_log_buf, 0x00, m_log_buff_size);
    log_max_lines_ = log_max_lines;

    //  设置文件输出名称
    time_t t_time = time(nullptr);
    struct tm t_tm;
    localtime_r(&t_time, &t_tm);
    m_today = t_tm.tm_mday;
    //  获取路径中的文件、路径
    size_t pos = file_path.rfind('/');
    if(pos == string::npos) {
        perror("LogFileNameError");
        return false;
    }
    string file_name = file_path.substr(pos+1);
    string dir_path = file_path.substr(0, pos + 1);
    //  文件名称添加日期
    char data_prefix[32];
    memset(data_prefix, 0x00, sizeof(data_prefix));
    snprintf(data_prefix, sizeof(data_prefix), "%d_%02d_%02d_", t_tm.tm_year + 1900 , t_tm.tm_mon + 1, t_tm.tm_mday);
    //  重新组成新的文件名
    string log_file_name = dir_path + data_prefix + file_name;

    //  打开文件
    m_fp = fopen(log_file_name.c_str(), "a+");
    if(m_fp == NULL) {
        return false;
    }

    return true;
}