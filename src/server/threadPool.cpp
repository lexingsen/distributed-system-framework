#include "threadPool.h"


ThreadPool::ThreadPool(int threadCnt) : m_threadCnt(threadCnt) {
  for (int i=0; i<m_threadCnt; ++i) {
    m_pool.push_back(new Thread());
  }
}

ThreadPool::~ThreadPool() {
  for (int i=m_pool.size()-1; i>=0; i--) {
    delete m_pool[i];
    m_pool.pop_back();
  }
}


int ThreadPool::getSubThreadSocketPairFd() {
  static int robin = 0;
  int x = m_pool[robin ++ % m_threadCnt]->getSocketPairFdFirst();
  std::cout << "=========== thread pressure ===========" << std::endl;
  for (int i=0; i<m_pool.size(); ++i) {
    std::cout << m_pool[i]->getId() << ":" << m_pool[i]->getEventMapSize() << std::endl;
  }
  std::cout << "=======================================" << std::endl;
  return x;
}