#include "log.h"

Log::Log() {
    m_log_buff_size = 0;
    m_block_queue = nullptr;
    m_fp = nullptr;
    m_log_buff = nullptr;
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

void Log::Async_Write_Log() {
    string single_log;
    while(m_block_queue->Pop(single_log)) {
        m_mutex.lock();
        if(nullptr != m_fp) {
            fputs(single_log.c_str(), m_fp);
        }
        m_mutex.unlock();
    }
}

Log & Log::GetInstance() {
    static Log m_instance;
    return m_instance;
}

void * Log::Flush_Log_Thread(void * arg) {
    Log::GetInstance().Async_Write_Log();
}

bool Log::Init(string file_path, LogStatus log_status, int log_buf_size, int log_max_lines, int maxQueueSize, LogWriteMode logWriteMode) {
    //  若日志写入方式为异步写，则初始化阻塞队列，并创建线程进行读写
    if(LogWriteMode::Async == logWriteMode) {
        m_isAsync = true;
        m_block_queue = new BlockQueue<string>(maxQueueSize);
        pthread_t tid;
        pthread_create(&tid, NULL, Flush_Log_Thread, NULL);
    }
    //  初始化日志参数
    m_log_status =  log_status;
    m_log_buff_size = log_buf_size;
    m_log_buff = new char[log_buf_size];
    memset(m_log_buff, 0x00, m_log_buff_size);
    m_log_max_lines = log_max_lines;
    //  获取路径中的文件、路径
    size_t pos = file_path.rfind('/');
    if(pos == string::npos) {
        perror("LogFileNameError");
        return false;
    }
    string file_name = file_path.substr(pos + 1);
    string dir_path = file_path.substr(0, pos + 1);
    //  文件名称添加日期
    time_t t_time = time(nullptr);
    struct tm t_tm;
    localtime_r(&t_time, &t_tm);
    m_today = t_tm.tm_mday;
    char data_prefix[32] = {0};
    snprintf(data_prefix, sizeof(data_prefix), "%d_%02d_%02d_", t_tm.tm_year + 1900 , t_tm.tm_mon + 1, t_tm.tm_mday);
    //  重新组成新的文件名
    string log_file_name = dir_path + data_prefix + file_name;
    m_logFileName = file_name;
    //  打开文件
    m_fp = fopen(log_file_name.c_str(), "a+");
    if(m_fp == NULL) {
        return false;
    }
    return true;
}

LogStatus Log::GetLogStatus() const {
    return m_log_status;
}

//  TODO：实现函数
void Log::WriteLog(int level, const char *format, ...) {
    //  判断日志等级
    std::string t_log_error_level;
    switch(level) {
        case 0 : t_log_error_level = "[debug]: "; break;
        case 1 : t_log_error_level = "[info]: "; break;
        case 2 : t_log_error_level = "[warn]: "; break;
        case 3 : t_log_error_level = "[error]: "; break;
        default : t_log_error_level = "[info]: "; break;
    }

    //  判断是否创建文件，更新文件指针
    m_mutex.lock();
    m_line_count++;
    time_t t_time = time(NULL);
    struct tm t_tm_time;
    localtime_r(&t_time, &t_tm_time);
    if(m_today != t_tm_time.tm_mday || m_line_count / m_log_max_lines != 0) {
        //  将缓冲区的内容写入文件
        fflush(m_fp);
        fclose(m_fp);
        //  整理文件名
        char t_file_name[30];
        memset(t_file_name, 0x00, sizeof(t_file_name));
        if(m_today != t_tm_time.tm_mday) {
            snprintf(t_file_name, sizeof(t_file_name), "%4d_%02d_%02d_%s", t_tm_time.tm_year + 1900, t_tm_time.tm_mon + 1, t_tm_time.tm_mday, m_logFileName.c_str());
        }
        else {
            snprintf(t_file_name, sizeof(t_file_name), "%4d_%02d_%02d_%s_%d", t_tm_time.tm_year + 1900, t_tm_time.tm_mon + 1, t_tm_time.tm_mday, m_logFileName.c_str(), m_line_count / m_log_max_lines);
        }
        m_fp = fopen(t_file_name, "a+");   
    }
    m_mutex.unlock();

    //  整理写入内容
    m_mutex.lock();
    va_list valst;
    va_start(valst, format);
    int log_write_head_len = snprintf(m_log_buff, m_log_buff_size, "%4d-%02d-%02d %02d:%02d:%02d %s", t_tm_time.tm_year + 1900, t_tm_time.tm_mon + 1, t_tm_time.tm_mday, t_tm_time.tm_hour, t_tm_time.tm_min, t_tm_time.tm_sec, t_log_error_level.c_str());
    int log_write_content_len = vsnprintf(m_log_buff + log_write_head_len, m_log_buff_size - log_write_head_len, format, valst);
    m_log_buff[log_write_head_len + log_write_content_len] = '\n';
    m_log_buff[log_write_head_len + log_write_content_len + 1] = '\0';
    std::string t_str_write_content(m_log_buff);
    va_end(valst);
    m_mutex.unlock();

    //  写入 - 判断异步写还是直接写入
    if(m_isAsync && ! m_block_queue->IsFull()) {
        m_block_queue->Push(string(m_log_buff));
    }
    else {
        m_mutex.lock();
        fputs(m_log_buff, m_fp);
        m_mutex.unlock();
    }
}
