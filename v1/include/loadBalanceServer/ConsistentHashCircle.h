#pragma once

#include <map>
#include <string>
#include "HashFunction.h"
#include "PysicalNode.h"
#include "VirtualNode.h"

class ConsistentHashCircle{
public:
    ConsistentHashCircle(HashFunction* fun);
    ~ConsistentHashCircle();
    void setHashFunction(HashFunction* fun);
    int addVirtualNode(PhysicalNode* node);
    int removeVirtualNode(PhysicalNode* node);
    int getVirtualNodeCnt();
    PhysicalNode* searchPhysicalNode(const std::string& sock);
private:
    HashFunction* m_fun;
    int m_virtualNodeCnt;
    std::map<unsigned long, VirtualNode*>* m_virtualNodeMap;
};