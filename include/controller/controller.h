#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <unordered_map>
#include <string>
#include <map>
#include "view.h"
#include "public.h"

class Controller {
private:
    std::map<int, View*> m_bizTypeMap;
    
public:
    void process(int fd, std::string& data);
    Controller();
    ~Controller();
};


#endif