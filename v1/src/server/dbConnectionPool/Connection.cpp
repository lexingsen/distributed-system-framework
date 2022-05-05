#include "logger.h"
#include "connection.h"
#include <iostream>


Connection::Connection() {
  m_conn = mysql_init(nullptr);
}

Connection::~Connection() {
  if (m_conn != nullptr) {
    mysql_close(m_conn);
  }
}

bool Connection::connect(std::string ip, unsigned short port,
std::string userName, std::string password, std::string dbName) {
  MYSQL* p = mysql_real_connect(m_conn, ip.c_str(), userName.c_str(),
    password.c_str(), dbName.c_str(), port, nullptr, 0);
    return p != nullptr;
}

bool Connection::update(std::string&& sql) {
  if (!mysql_query(m_conn, sql.c_str())) {
    LOG_FUNC_MSG("mysql_query()", "update success!");
    return true;
  }
  return false;
}

MYSQL_RES* Connection::query(std::string&& sql) {
  if (mysql_query(m_conn, sql.c_str())) {
    LOG_FUNC_MSG("mysql_query()", "query success!");
    return nullptr;
  }
  return mysql_use_result(m_conn);
}



