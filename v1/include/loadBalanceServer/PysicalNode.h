#pragma once
#include <string>

class PhysicalNode {
private:  
    int m_cnt;
    std::string m_ip;
    unsigned short m_port;
public:
    PhysicalNode();
    PhysicalNode(int cnt, const std::string& ip, unsigned short port);
    int getVirtualNodeCnt();
    void setPhysicalNode(const std::string& ip, unsigned short port);
    std::string getIp();
    unsigned short getPort();
};