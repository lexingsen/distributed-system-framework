#include "PysicalNode.h"



PhysicalNode::PhysicalNode():m_cnt(0) {}

PhysicalNode::PhysicalNode(int cnt, const std::string& ip, unsigned short port):
    m_cnt(cnt),m_ip(ip), m_port(port) {}

void PhysicalNode::setPhysicalNode(const std::string& ip, unsigned short port) {
    this->m_ip = ip;
    this->m_port = port;
}

int PhysicalNode::getVirtualNodeCnt() {
    return m_cnt;
}

unsigned short PhysicalNode::getPort() {
    return m_port;
}

std::string PhysicalNode::getIp() {
    return m_ip;
}