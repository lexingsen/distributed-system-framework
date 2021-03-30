#include "view.h"
#include "db.h"
#include "logger.h"
#include "connectionPool.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>



LoginView::LoginView() {
  
}

LoginView::~LoginView() {
}

void LoginView::process(int fd, Json::Value& value) {
  LOG_FUNC_TRACE();
  std::string name = value["name"].asString();
  std::string password = value["password"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "select count(*) from user where name=\'%s\' and password=\'%s\' limit 1;", name.c_str(), password.c_str());
  MYSQL_RES* mysqlRes = ConnectionPool::getInstance()->getConnection()->query(std::move(std::string(sql)));
  //MYSQL_RES* mysqlRes = MySQL::getInstance()->query(std::string(sql));
  
  Json::Value res;
  if (mysqlRes == nullptr) {
    res["message"] = "login fail!";
  } else {
    res["message"] = "login success!";
  }
  send(fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
  
}

RegisterView::RegisterView() {

}


RegisterView::~RegisterView() {

}

void RegisterView::process(int fd, Json::Value& value) {
  std::string name = value["name"].asString();
  std::string password = value["password"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "insert into user values()");
  bool insertStatus = ConnectionPool::getInstance()->getConnection()->update(std::move(std::string(sql)));
  Json::Value res;
  if (insertStatus == true) {
    res["message"] = "register success!";
  } else {
    res["message"] = "register fail!";
  }
  send(fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str(), 0);
}

InsertView::InsertView() {

}

InsertView::~InsertView() {

}

void InsertView::process(int fd, Json::Value& value) {
  LOG_FUNC_TRACE();
  int id = value["id"].asInt();
  std::string id_card = value["id_card"].asString();
  std::string name = value["name"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "insert into blacklist values(%d, \'%s\', \'%s\');", id, id_card.c_str(), name.c_str());
  MYSQL_RES* mysqlRes = MySQL::getInstance()->query((std::string(sql)));
  Json::Value res;
  if (mysqlRes != nullptr) {
    res["message"] = "insert into blacklist success!";
  } else {
    res["message"] = "insert into blacklist fail!";
  }
  send(fd, value.toStyledString().c_str(), strlen(value.toStyledString().c_str()), 0);
}

QueryView::QueryView() {

}

QueryView::~QueryView() {

}

void QueryView::process(int fd, Json::Value& value) {
  
}