
#include "controller.h"
#include "json.h"
#include "view.h"
#include "logger.h"
#include <iostream>

Controller::Controller() {
    m_bizTypeMap.insert(std::make_pair(LOGIN, new LoginView()));
    m_bizTypeMap.insert(std::make_pair(REGISTER, new RegisterView()));
}   

Controller::~Controller() {

}




void Controller::process(int fd, std::string& data) {
    // data(string) -> json(string)
    // // decode
    
    using namespace nlohmann;
    nlohmann::json j = nlohmann::json::parse(data);
    LOG_INFO << data;
    LOG_INFO << "type:" <<  j["bizType"].get<int>();
    int bizType = j["bizType"].get<int>();
    m_bizTypeMap[bizType]->process(fd, data);
}


// int main() {
//     return 0;
// }