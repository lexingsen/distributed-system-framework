#ifndef __MYSQLDB_H__
#define __MYSQLDB_H__

#include <mysql/mysql.h>
#include <string>

// 设计成一个线程安全的mysql单例类   因为mysql是可以被多线程看到的
// raii
// client
class MySQLDB {
private:
    MYSQL* m_mysqlClient;
    MySQLDB() {
        m_mysqlClient = NULL;
    }
public:
    static MySQLDB* GetInstance() {
        static MySQLDB res;
        return &res;
    }
    // mysql -h x.x.x.x -P 3307 -u root -p
    // crud c-create r-retrieve u-update d-delete
    // 建库-》建表-》插入数据
    void Connect(const std::string& ip, unsigned short port, const std::string& user, const std::string& password,
        const std::string& db);
    bool Insert(std::string&& sql);
    int Query(std::string&& sql);

    ~MySQLDB();
};

#endif