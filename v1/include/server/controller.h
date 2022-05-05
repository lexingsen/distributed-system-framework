#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <map>
#include <json/json.h>
#include "view.h"
#include "logger.h" 


class Controller {
private:
  std::map<int, View*> m_modelMap;
public:
  Controller();
  ~Controller();
  void process(int fd, Json::Value& value);
};

#endif 

