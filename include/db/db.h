/*
 * @Description: 封装mysql API为MySQL类
 * @Language: C++
 * @Author: Li Si cheng
 * @Date: 2021-03-29 03:55:54
 */

#ifndef __DB_H__
#define __DB_H__

#include <mysql/mysql.h>
#include <string>

class MySQL {
private:
  MYSQL* m_conn;
public:
  MySQL();
  ~MySQL();

  bool connect();

  bool update(const std::string& sql);

  MYSQL_RES* query(const std::string& sql);

  MYSQL* getConnection() const;
};


#endif