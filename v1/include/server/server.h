#ifndef _SERVER_H_
#define _SERVER_H_



#include "threadPool.h"
#include "tcpServer.h"
#include "tcpClient.h"
#include <event.h>

class Server {
public:
  Server(const std::string& ip, unsigned short port, int threadCnt);
  ~Server();
private:
  struct event_base* m_base;
  ThreadPool* m_pool;
  TcpClient* m_tcpClient;
  int m_listenFd;

  friend void listenClientConnectEventCallBack(int fd, short event, void *arg);
  friend void listenSubThreadSocketPairFirstIOEventCallBack(int fd, short event, void *arg);
};


#endif