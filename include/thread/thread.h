
#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

#include "logger.h"
/*  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine) (void *), void *arg); */

// one loop per thread
// raii

class Reactor;
class Controller;
class Thread {
private:
    pthread_t m_tid;
    int m_channel[2];
    Reactor* m_reactor;
    Controller* m_ctroller;
public:
    static void* taskFunc(void* arg);
    static void SocketPairEventCallBack(int fd, short events, void* arg);
    static void ClientIOEventCallBack(int fd, short events, void* arg);
    Thread();
    ~Thread();


    int GetSocketPairFirst() const;
    int GetSocketPairSecond() const;
    pthread_t GetTid() const;
};


#endif

