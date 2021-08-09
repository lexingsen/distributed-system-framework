#pragma once

#include "PysicalNode.h"
#include <string>

class VirtualNode {
private:
    long m_hashValue; // 虚拟节点对应的hash值
    PhysicalNode* m_father;
public:
    VirtualNode();
    VirtualNode(PhysicalNode* father);
    void setVirtualNode(PhysicalNode* father);
    PhysicalNode* getFatherPhysicalNode();
    void setHash(long hash);
    long getHash();
};
