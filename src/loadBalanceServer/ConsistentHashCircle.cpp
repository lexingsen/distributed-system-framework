#include <iostream>
#include "ConsistentHashCircle.h"
#include "logger.h"
#include "VirtualNode.h"


ConsistentHashCircle::ConsistentHashCircle(HashFunction* fun) {
    if (!fun) {
        LOG_FUNC_ERROR("parameter fun is nullptr");
        return;
    }
    this->m_fun = fun;
    this->m_virtualNodeCnt = 0;
    this->m_virtualNodeMap = new std::map<unsigned long, VirtualNode*>();
}


ConsistentHashCircle::~ConsistentHashCircle() {

}

void ConsistentHashCircle::setHashFunction(HashFunction* fun) {
    this->m_fun = fun;
}

int ConsistentHashCircle::addVirtualNode(PhysicalNode* node) {
    if (!node) {
        LOG_MSG("the physical node is null!");
        return -1;
    }
    if (node->getVirtualNodeCnt() <= 0) {
        LOG_MSG("the physical node has not virtual node!");
        return -1;
    }
    std::string sock = node->getIp() + std::to_string(node->getPort());

    std::string tmp = sock;
    VirtualNode* virtualNode;
    unsigned long hash;
    for (int i=0; i<node->getVirtualNodeCnt(); ++i) {
        virtualNode = new VirtualNode(node);
        tmp += std::to_string(i);
        hash = this->m_fun->getHashValue(tmp);
        auto it = m_virtualNodeMap->find(hash);
        if (it == m_virtualNodeMap->end()) {
        if (virtualNode) {
            m_virtualNodeMap->insert(std::make_pair(hash, virtualNode));
            this->m_virtualNodeCnt ++;
        }
        } else {
        LOG_MSG("find hash conflict!");
        return -1;
        }
        tmp = sock;
    }

    auto it = m_virtualNodeMap->begin();
    if (it == m_virtualNodeMap->end()) {
        std::cout << "there has no virtual node!"  << std::endl;
    } else {
        std::cout << "============ virtual node list ============" << std::endl;
        for (auto x=m_virtualNodeMap->begin(); x!=m_virtualNodeMap->end(); ++x) {
        std::cout << x->first << ":" << " ip:" << x->second->getFatherPhysicalNode()->getIp() << " port:" << x->second->getFatherPhysicalNode()->getPort() << std::endl;
        }
        std::cout << "===========================================" << std::endl;
    }

    std::cout << "success addPhysicalNode's virtual node!" << std::endl;
    return 0;
}

int ConsistentHashCircle::removeVirtualNode(PhysicalNode* node) {
    if (!node) return -1;
    std::string sock = node->getIp() + std::to_string(node->getPort());

    std::string tmp = sock;
    unsigned long hash = 0;
    for (int i=0; i<node->getVirtualNodeCnt(); ++i) {
        tmp += std::to_string(i);
        hash = m_fun->getHashValue(tmp);
        m_virtualNodeMap->erase(hash);
        m_virtualNodeCnt --;
        tmp = sock;
    }

    auto it = m_virtualNodeMap->begin();
    if (it == m_virtualNodeMap->end()) {
        std::cout << "there has no virtual node!"  << std::endl;
    } else {
        std::cout << "============ virtual node list ============" << std::endl;
        for (auto x=m_virtualNodeMap->begin(); x!=m_virtualNodeMap->end(); ++x) {
        std::cout << x->first << ":" << " ip:" << x->second->getFatherPhysicalNode()->getIp() << " port:" << x->second->getFatherPhysicalNode()->getPort() << std::endl;
        }
        std::cout << "===========================================" << std::endl;
    }
    std::cout << "success remove physicalNode's virtual node!" << std::endl;
    return 0;
}


PhysicalNode* ConsistentHashCircle::searchPhysicalNode(const std::string& sock) {
    unsigned long hash = this->m_fun->getHashValue(sock);
    auto it = m_virtualNodeMap->lower_bound(hash);
    if (it == m_virtualNodeMap->end()) {
        it = m_virtualNodeMap->begin();
    }
    VirtualNode* res = it->second;
    if (!res) {
        return nullptr;
    } else {
        return res->getFatherPhysicalNode();
    }
}

int ConsistentHashCircle::getVirtualNodeCnt() {
    return m_virtualNodeCnt;
}