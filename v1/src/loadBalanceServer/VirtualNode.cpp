#include "VirtualNode.h"

VirtualNode::VirtualNode() {

}

VirtualNode::VirtualNode(PhysicalNode* father) {
    this->m_hashValue = -1;
    this->m_father = father;
}
void VirtualNode::setVirtualNode(PhysicalNode* father) {
    this->m_father = father;
}

PhysicalNode* VirtualNode::getFatherPhysicalNode() {
    return this->m_father;
}

void VirtualNode::setHash(long hash) {
    this->m_hashValue = hash;
}

long VirtualNode::getHash() {
    return this->m_hashValue;
}