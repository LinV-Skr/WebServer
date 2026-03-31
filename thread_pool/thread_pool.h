#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "../mysql/sql_connection_pool.h"

#include <pthread.h>

template<typename T>
class thread_pool
{
public:
    thread_pool(int actor_model, Mysql_Connection_Pool * mysql_conn_pool, int thread_num, int max_request);
private:
    int m_actor_model;
    int m_thread_num;
    int m_max_request_num;
    Mysql_Connection_Pool * m_mysql_conn_pool;
    pthread_t * thread_pool;
};

#endif