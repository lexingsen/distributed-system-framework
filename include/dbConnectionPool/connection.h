#ifndef __CONNECTION_H__
#define __CONNECTION_H__
#include <mysql/mysql.h>
#include <ctime>
#include <string>


class Connection {
private:
  MYSQL* m_conn;
  // 进入空闲状态后起始的存活时间
  clock_t m_aliveTime;
public:
  Connection();
  ~Connection();

  bool connect(std::string ip, unsigned short port,
  std::string userName, std::string password, std::string dbName);

  bool update(std::string&& sql);
  MYSQL_RES* query(std::string&& sql);

  void refreshAliveTime() {
    m_aliveTime = clock();
  }

  clock_t getAliveTime() const {
    return clock() - m_aliveTime;
  }
};

#endif