#include "connectionPool.h"
#include "logger.h"

bool ConnectionPool::loadConfigFile() {
  FILE* pf = fopen("../../config/mysql.cfg", "r");
  if (nullptr == pf) {
    LOG_MSG("mysql.cfg file is not exist!");
    return false;
  }

  while (!feof(pf)) {
    char buf[BUF_LEN] = {0};
    fgets(buf, BUF_LEN, pf);
    std::string str = buf;
    int idx = str.find('=', 0);
    if (-1 == idx) {
      continue;
    }

    int endIdx = str.find('\n', idx);
    std::string key   = str.substr(0, idx);
    std::string value = str.substr(idx+1, endIdx-idx-1);
    if (key == "ip") {
      m_ip = value;
    } else if (key == "port") {
      m_port = atoi(value.c_str());
    } else if (key == "dbName") {
      m_dbName = value;
    } else if (key == "password") {
      m_password = value;
    } else if (key == "userName") {
      m_userName = value;
    } else if (key == "initSize") {
      m_initSize = atoi(value.c_str());
    } else if (key == "maxIdleTime") {
      m_maxIdleTime = atoi(value.c_str());
    } else if (key == "maxSize") {
      m_maxSize = atoi(value.c_str());
    } else if (key == "connectionTimeOut") {
      m_connectionTimeOut = atoi(value.c_str());
    }
  }
  return true;
}


ConnectionPool::ConnectionPool() {
  if (!loadConfigFile()) {
    return;
  }
  
  for (int i = 0; i < m_initSize; ++i) {
    Connection *p = new Connection();
    p->connect(m_ip, m_port, m_userName, m_password, m_dbName);
    p->refreshAliveTime();
    m_connectionQueue.push(p);
    m_connectionCnt ++;
  }

  std::thread producer(std::bind(&ConnectionPool::produceConnectionTask, this));
  producer.detach();

  std::thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
  scanner.detach();
}

void ConnectionPool::produceConnectionTask() {
  for (;;) {
    std::unique_lock<std::mutex> lock(m_queueMutex);
    while (!m_connectionQueue.empty()) {
      m_cv.wait(lock);
    }
    if (m_connectionCnt < m_maxSize) {
      Connection * p = new Connection();
      p->connect(m_ip, m_port, m_userName, m_password, m_dbName);
      p->refreshAliveTime();
      m_connectionQueue.push(p);
      m_connectionCnt ++;
    }
    m_cv.notify_all();
  }
}

std::shared_ptr<Connection> ConnectionPool::getConnection() {
  std::unique_lock<std::mutex> lock(m_queueMutex);
  while (m_connectionQueue.empty()) {
    if (std::cv_status::timeout == m_cv.wait_for(lock, std::chrono::milliseconds(m_connectionTimeOut))) {
      if (m_connectionQueue.empty()) {
        LOG_MSG("connection timeout get connection fail!");
        return nullptr;
      }
    }
  }

  std::shared_ptr<Connection> sp(m_connectionQueue.front(), 
  [&](Connection* pconn) {
    std::unique_lock<std::mutex> lock(m_queueMutex);
    pconn->refreshAliveTime();
    m_connectionQueue.push(pconn);
    m_connectionCnt ++;
  });
  m_connectionQueue.pop();
  m_connectionCnt --;
  m_cv.notify_all();
  return sp;
}


void ConnectionPool::scannerConnectionTask() {
  for (;;) {
    std::this_thread::sleep_for(std::chrono::seconds(m_maxIdleTime));

    std::unique_lock<std::mutex> lock(m_queueMutex);
    while (m_connectionCnt > m_initSize) {
      Connection* p = m_connectionQueue.front();
      if (p->getAliveTime() >= (m_maxIdleTime * 1000)) {
        m_connectionQueue.pop();
        m_connectionCnt --;
        delete p;
      } else {
        break;
      }
    }
  }
}