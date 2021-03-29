#ifndef __DB_H__
#define __DB_H__

#include <mysql/mysql.h>
#include <string>

class MySQL {
private:
  MYSQL* m_conn;
public:
  static MySQL* getInstance() {
    static MySQL res;
    return &res;
  }

  bool connect();

  bool update(const std::string& sql);

  MYSQL_RES* query(const std::string& sql);

  MYSQL* getConnection() const;
private:  
  MySQL();
  ~MySQL();
};


#endif