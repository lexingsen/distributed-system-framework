#include "controller.h"


Controller::Controller() {
  m_modelMap.insert(std::make_pair(EN_LOGIN, new LoginView()));
  m_modelMap.insert(std::make_pair(EN_REGISTER, new RegisterView()));
  m_modelMap.insert(std::make_pair(EN_INSERT, new InsertView()));
  m_modelMap.insert(std::make_pair(EN_QUERY, new QueryView()));
  m_modelMap.insert(std::make_pair(EN_INFORMATION_COLLECTOR, new InformationCollectorView()));
}

Controller::~Controller() {
  for (auto x=m_modelMap.begin(); x!=m_modelMap.end(); ++x) {
    delete x->second;
  }
}

void Controller::process(int fd, Json::Value& value) {
  LOG_FUNC_TRACE();
  m_modelMap[value["type"].asInt()]->process(fd, value);
}