/*
 * @Description: 
 * @Language: 
 * @Author: 
 * @Date: 2021-03-26 01:43:34
 */
#ifndef _THREAD_H_
#define _THREAD_H_

#include "controller.h"
#include "public.h"
#include <unistd.h>
#include <json/json.h>
#include <pthread.h>
#include <sys/types.h>
#include <map>
#include <event.h>
#include <iostream>


class Thread {
private:
  pthread_t m_id;
  std::map<int, struct event*>* m_eventMap;
  int m_socketpairFd[2];
  struct event_base* m_base;
  Controller* m_controller;
  friend void clientIOEventCallBack(int fd, short event, void *arg);
  friend void socketPairIOEventCallBack(int fd, short event, void *arg);
  friend void* threadTaskFunction(void *arg);
public:
  Thread();
  ~Thread();
  int getEventMapSize();
  int getSocketPairFdFirst();
  int getSocketPairFdSecond();
  pthread_t getId();
};

#endif