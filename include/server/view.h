#ifndef _VIEW_H_
#define _VIEW_H_
#include <json/json.h>
#include "db.h"

class View {
public:
  virtual void process(int fd, Json::Value &value) = 0;
};

class InformationCollectorView : public View {
public:
  InformationCollectorView();
  ~InformationCollectorView();

  void process(int fd, Json::Value& value);  
};

class LoginView : public View {
public:
  LoginView();
  ~LoginView();

  void process(int fd, Json::Value &value);
};

class RegisterView : public View {
public:
  RegisterView();
  ~RegisterView();
  void process(int fd, Json::Value &value);
};

class InsertView : public View {
public:
  InsertView();
  ~InsertView();
  void process(int fd, Json::Value &value);
};

class QueryView : public View {
public:
  QueryView();
  ~QueryView();
  void process(int fd, Json::Value &value);
};


#endif