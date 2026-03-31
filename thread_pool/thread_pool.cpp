#include "thread_pool.h"

template<typename T>
thread_pool<T>::thread_pool(int actor_model, Mysql_Connection_Pool * mysql_conn_pool, int thread_num, int max_quest_num)
{
    m_actor_model = actor_model;
    m_thread_num = thread_num;
    m_max_request_num = max_quest_num;
    m_mysql_conn_pool = mysql_conn_pool;

    if(0 >= m_thread_num || 0 >= m_max_request_num)
    {
        LOG_ERROR("Thread Pool Init Error");
        throw runtime_error();
    }
}