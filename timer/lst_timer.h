#ifndef LST_TIMER_H
#define LST_TIMER_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>

class util_timer;

struct client_data
{
    sockaddr_in address;
    int sockfd;
    util_timer * timer;
};

class util_timer
{
public:
    util_timer() : m_prev(NULL), m_next(NULL){}
public:
    //  回调函数 - 成员变量
    void (* cb_func)(client_data *);
    //  结束时间
    time_t m_expire;
    //  互相引用，用户数据
    client_data * m_user_data;
    //  链表指针
    util_timer * m_prev;
    util_timer * m_next;
};

#endif