#include "view.h"
#include "json.h"
#include "redis.h"
#include "logger.h"
#include "mysqldb.h"

#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>
#include <sstream>

// login 业务
// {"bizType":0,"name":"fxx","password":"456"}
// {"bizType":1,"name":"fxx","password":"456"}
// {"bizType":0,"name":"lsc","password":"123"}
void LoginView::process(int fd, std::string& data) {
    // decode compute encode send
    // LOG_INFO << data;
    // nlohmann::json j = nlohmann::json::parse(data);
    // LOG_INFO << j["name"].get<std::string>();
    // LOG_INFO << j["password"].get<std::string>();
    
    nlohmann::json j = nlohmann::json::parse(data);
    std::string name = j["name"].get<std::string>();
    std::string password = j["password"].get<std::string>();
    //std::string res = Redis::GetInstance()->Get(name);
    std::stringstream ss;
    ss << "select * from user where name=\"" << name << "\" and password=\"" << password << "\";";
    
    
    std::string res = "login fail!\n";
    if (MySQLDB::GetInstance()->Query(std::move(ss.str()))) {
        res = "login success!\n";
    }
    send(fd, res.c_str(), strlen(res.c_str()), 0);
}


// "{\"bizType\":1,\"name\":\"lsc\",\"password\":\"123\"}"

// {"bizType":1,"name":"lsc","password":"123"}

void RegisterView::process(int fd, std::string& data) {
    // decode compute encode send
    // LOG_INFO << data;
    // nlohmann::json j = nlohmann::json::parse(data);
    // LOG_INFO << j["name"].get<std::string>();
    // LOG_INFO << j["password"].get<std::string>();
    nlohmann::json j = nlohmann::json::parse(data);
    std::string name = j["name"].get<std::string>();
    std::string password = j["password"].get<std::string>();

    std::stringstream ss;
    static int id = 1;
    ss << "insert into user(name, password) values(\"" << name << "\", \"" << password << "\");"; 
    
    std::string res = "register failed!\n";
    if (MySQLDB::GetInstance()->Insert(std::move(ss.str()))) {
        res = "register success!\n";
    }
    ::send(fd, res.c_str(), strlen(res.c_str()), 0);
}

// int main() {
//     return 0;
// }