#ifndef __VIEW_H__
#define __VIEW_H__


#include <string>
// interface 抽象的
class View {
public:
    virtual void  process(int fd, std::string& data) = 0;
};

class LoginView : public View {
public:
    void process(int fd, std::string& data);
};

class RegisterView : public View {
public:
    void process(int fd, std::string& data);
};


#endif