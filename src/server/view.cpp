#include "view.h"
#include "db.h"
#include "logger.h"
#include "connectionPool.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>


InformationCollectorView::InformationCollectorView() {}
InformationCollectorView::~InformationCollectorView() {}

void InformationCollectorView::process(int fd, Json::Value& value) {
  LOG_FUNC_TRACE();
  std::string name = value["name"].asString();
  std::string id_card = value["id_card"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "select count(*) from blacklist where name=\'%s\' and id_card=\'%s\' limit 1;", name.c_str(), id_card.c_str());
  bool queryStatus = ConnectionPool::getInstance()->getConnection()->query(std::move(std::string(sql)));
  Json::Value res;
  if (queryStatus == true) {
    res["message"] = "this tourist is exist in blacklist!";
  } else {
    res["message"] = "this tourist is not exist in blacklist!";
  }
  send(fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
}


LoginView::LoginView() {}
LoginView::~LoginView() {}
void LoginView::process(int fd, Json::Value& value) {
  LOG_FUNC_TRACE();
  std::string name = value["name"].asString();
  std::string password = value["password"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "select count(*) from user where name=\'%s\' and password=\'%s\' limit 1;", name.c_str(), password.c_str());
  MYSQL_RES* logStatus = ConnectionPool::getInstance()->getConnection()->query(std::move(std::string(sql)));
  
  Json::Value res;
  if (logStatus != nullptr) {
    res["message"] = "login success!";
  } else {
    res["message"] = "login fail!";
  }
  send(fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
  
}

RegisterView::RegisterView() {}
RegisterView::~RegisterView() {}
void RegisterView::process(int fd, Json::Value& value) {
  std::string name = value["name"].asString();
  std::string password = value["password"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "insert into user(name, password) values(\'%s\', \'%s\');", name.c_str(), password.c_str());
  std:: cout << "sql:" << sql << std::endl;
  bool registerStatus = ConnectionPool::getInstance()->getConnection()->update(std::move(std::string(sql)));
  Json::Value res;
  if (registerStatus == true) {
    res["message"] = "register success!";
  } else {
    res["message"] = "register fail!";
  }
  send(fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
}

InsertView::InsertView() {}
InsertView::~InsertView() {}
void InsertView::process(int fd, Json::Value& value) {
  LOG_FUNC_TRACE();
  std::string id_card = value["id_card"].asString();
  std::string name = value["name"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "insert into blacklist(id_card, name) values(\'%s\', \'%s\');",id_card.c_str(), name.c_str());
  std:: cout << "sql:" << sql << std::endl;
  bool insertStatus = ConnectionPool::getInstance()->getConnection()->update(std::move(std::string(sql)));
  Json::Value res;
  if (true == insertStatus) {
    res["message"] = "insert into blacklist success!";
  } else {
    res["message"] = "insert into blacklist fail!";
  }
  send(fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
}

QueryView::QueryView() {}
QueryView::~QueryView() {}
void QueryView::process(int fd, Json::Value& value) {
  std::string name = value["name"].asString();
  std::string idCard = value["id_card"].asString();
  char sql[SQL_LEN] = {0};
  sprintf(sql, "select count(*) from blacklist where name=\'%s\' and id_card=\'%s\' limit 1", name.c_str(), idCard.c_str());
  bool logStatus = ConnectionPool::getInstance()->getConnection()->query(std::move(std::string(sql)));
  
  Json::Value res;
  if (logStatus == true) {
    res["message"] = "this tourist is not exist!";
  } else {
    res["message"] = "this tourist is exist!";
  }
  send(fd, value.toStyledString().c_str(), strlen(value.toStyledString().c_str()), 0);
}
