#ifndef BLOCK_QUEUE_H
#define BLOCK_QUEUE_H

#include "../lock/locker.h"

#include <sys/time.h>

//  循环数组实现的阻塞队列
//  线程安全，每个操作前都加互斥锁，操作完成后，再解锁
template<class T>
class BlockQueue {
public:
    BlockQueue(int maxSize = 1000) {
        if(maxSize <= 0)
            exit(-1);

        m_maxSize = maxSize;
        m_arrry = new T[m_maxSize];
        m_size = 0;
        m_front = -1;
        m_back = -1;
    }

    ~BlockQueue() {
        m_mutex.lock();
        if(m_arrry != NULL) {
            delete [] m_arrry;
            m_arrry = nullptr;
        }
        m_mutex.unlock();
    }

    void Clear() {
        m_mutex.lock();
        m_front = -1;
        m_back = -1;
        m_size = 0;
        m_mutex.unlock();
    }

    bool IsFull() {
        m_mutex.lock();
        if(m_size >= m_maxSize) {
            m_mutex.unlock();
            return true;
        }
        m_mutex.unlock();
        return false;
    }

    bool IsEmpty() {
        m_mutex.lock();
        if(0 == m_size) {
            m_mutex.unlock();
            return true;
        }
        m_mutex.unlock();
        return false;
    }

    bool GetFront(T & value) {
        m_mutex.lock();
        if(0 == m_size) {
            m_mutex.unlock();
            return false;
        }
        value = m_arrry[m_front];
        m_mutex.unlock();
        return true;        
    }

    bool GetBack(T & value) {
        m_mutex.lock();
        if(0 == m_size) {
            m_mutex.unlock();
            return false;
        }
        value = m_arrry[m_back];
        m_mutex.unlock();
        return true;
    }

    int Size() {
        int t_size;
        m_mutex.lock();
        t_size = m_size;
        m_mutex.unlock();
        return t_size;
    }

    int MaxSize() {
        int t_max_size;
        m_mutex.lock();
        t_max_size = m_maxSize;
        m_mutex.unlock();
        return t_max_size;
    }

    //  生产者生产元素
    bool Push(const T & item) {
        m_mutex.lock();
        if(m_size >= m_maxSize) {
            //  阻塞队列满，唤醒所有等待线程
            m_cond.broadcast();
            m_mutex.unlock();
            return false;
        }
        //  生产元素
        m_back = (m_back + 1) % m_maxSize;
        m_arrry[m_back] = item;
        m_size = m_size + 1;
        //  唤醒等待线程
        m_cond.broadcast();
        m_mutex.unlock();
        return true;
    }

    //  消费者消费元素
    bool Pop(T & item) {
        m_mutex.lock();
        //  防止被虚假唤醒
        while(m_size <= 0) {
            if(!m_cond.wait(&m_mutex.m_mutex)) {
                m_mutex.unlock();
                return false;
            }
        }
        m_front = (m_front + 1) % m_maxSize;
        item = m_arrry[m_front];
        m_size--;
        m_mutex.unlock();
        return true;
    }

    //  消费者消费元素，添加超时退出
    bool Pop(T & item, int ms_timeout) {
        m_mutex.lock();
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += ms_timeout;
        while(m_size <= 0) {
            if(!m_cond.time_wait(&m_mutex.m_mutex, ts)) {
                m_mutex.unlock();
                return false;
            }
        }
        m_front = (m_front + 1) % m_maxSize;
        item = m_arrry[m_front];
        m_size--;
        m_mutex.unlock();
        return true;
    }

private:
    //  阻塞队列最大大小
    int m_maxSize;
    //  循环数组
    T * m_arrry;
    //  循环数组实际大小
    int m_size;
    //  循环数组头指针
    int m_front;
    //  循环数组尾指针
    int m_back;
    //  互斥变量
    locker m_mutex;
    //  条件变量
    cond m_cond;
};

#endif