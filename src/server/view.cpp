#include "view.h"
#include "db.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>


LoginView::LoginView() {

}

LoginView::~LoginView() {
}

void LoginView::process(int fd, Json::Value& value) {
  std::string name = value["name"].asString();                        
  std::string password = value["password"].asString();
  MySQL::getInstance()->connect();
  char sql[1024] = {0};
  sprintf(sql, "select count(*) form user where name=%s and password=%s limit 1", name.c_str(), password.c_str());
  MYSQL_RES* mysqlRes = MySQL::getInstance()->query(std::string(sql));
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

}

InsertView::InsertView() {

}

InsertView::~InsertView() {

}

void InsertView::process(int fd, Json::Value& value) {

}

QueryView::QueryView() {

}

QueryView::~QueryView() {

}

void QueryView::process(int fd, Json::Value& value) {
  
}