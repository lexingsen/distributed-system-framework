#include "mysqldb.h"
#include "public.h"
#include "logger.h"

#include <string>
#include <sstream>
#include <iostream>


void MySQLDB::Connect(const std::string& ip, unsigned short port, const std::string& user, const std::string& password,
    const std::string& db) {
    m_mysqlClient = mysql_init(nullptr);
    // 三次握手 认证 鉴权  xxx  四次挥手  10s  1s
    // 连接池  初始连接量 最大连接量  最大的等待时间(空闲时间)10s
    if (!mysql_real_connect(m_mysqlClient,   
            ip.c_str(), user.c_str(), password.c_str(), db.c_str(), 3306, nullptr, 0)) {
        LOG_ERROR << "mysql_real_connect() failed!";
    }
    LOG_INFO << "mysql connect success!";
}


// snprintf /  stringstream

int MySQLDB::Query(std::string&& sql) {
    // return value
    LOG_INFO << "sql:" << sql;
    // 执行成功返回0
    if (mysql_query(m_mysqlClient, sql.c_str())) {
        LOG_ERROR <<  mysql_error(m_mysqlClient);
        return 0;
    }
    return mysql_num_rows(mysql_store_result(m_mysqlClient));
}

bool MySQLDB::Insert(std::string&& sql) {
    // return value
    LOG_INFO << "sql:" << sql;
    // 执行成功返回0
    if (mysql_query(m_mysqlClient, sql.c_str())) {
        LOG_ERROR <<  mysql_error(m_mysqlClient);
        return false;
    }
    return true;
}

MySQLDB::~MySQLDB() {
    if (m_mysqlClient != nullptr) {
        mysql_close(m_mysqlClient);
    }
}


// int main() {
//     MySQLDB* m = MySQLDB::GetInstance();
//     m->Connect(MYSQL_IP, lsc::MYSQLDB_PORT, USER, PASSWORD, DB);


//     // // snprintf   sstrem
//     // char sql[LARGE_BUF_LEN] = {0};
//     std::string name = "xcg";
//     std::string password = "345";

//     std::stringstream ss;
//     ss << "select * from user where name=\"" << name << "\" and password=\"" << password << "\" limit 1;";
//     // snprintf(sql, LARGE_BUF_LEN, "select * from user where name = %s and password = %s", name.c_str(), password.c_str());

//     std::cout << m->Query(std::move(ss.str())) << std::endl;
// }
