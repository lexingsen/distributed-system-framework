#ifndef __DB_CONNECTION_POOL_H__
#define __DB_CONNECTION_POOL_H__

#include <string>
#include <queue>
#include <iostream>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <memory>
#include <functional>
#include "connection.h"


class ConnectionPool {
private:
  ConnectionPool();
public:
  static ConnectionPool* getInstance() {
    static ConnectionPool pool;
    return &pool;
  }
  // 给外部提供接口，从连接池中获取一个可用的空闲连接
  std::shared_ptr<Connection> getConnection();
  
private:
  bool loadConfigFile();
  // 独立的线程，负责生产新连接
  void produceConnectionTask();
  // 扫描超过maxIdleTime时间的空闲连接，收回连接
  void scannerConnectionTask();

  std::string m_ip;
  std::string m_userName;
  std::string m_password;
  std::string m_dbName;
  int m_initSize;
  int m_maxSize;
  int m_maxIdleTime;
  int m_connectionTimeOut;
  unsigned short m_port;
  

  std::queue<Connection*> m_connectionQueue;
  std::mutex m_queueMutex;
  std::atomic_int m_connectionCnt;
  std::condition_variable m_cv;

};




#endif