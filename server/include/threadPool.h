#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "thread.h"
#include <vector>

class ThreadPool {
public:
  ThreadPool(int threadCnt);
  ~ThreadPool();
  int getSubThreadSocketPairFd();
private:
  int m_threadCnt;
  std::vector<Thread*> m_pool;  
};



#endif