#include "controller.h"


Controller::Controller() {
  m_modelMap.insert(make_pair(LOGIN, new LoginView()));
  m_modelMap.insert(make_pair(REGISTER, new RegisterView()));
  m_modelMap.insert(make_pair(INSERT, new InsertView()));
  m_modelMap.insert(make_pair(QUERY, new QueryView()));
}

Controller::~Controller() {
  for (auto x=m_modelMap.begin(); x!=m_modelMap.end(); ++x) {
    delete x->second;
  }
}

void Controller::process(int fd, Json::Value& value) {
  m_modelMap[value["type"].asInt()]->process(fd, value);
}