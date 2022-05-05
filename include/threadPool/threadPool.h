#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

class Thread;

#include <vector>
class ThreadPool {
private:
    std::vector<Thread*> m_pool;
    int m_numberOfThread;
public:
    ThreadPool(int numberOfThread);
    ~ThreadPool();

    int GetNumberOfThread() const;

    int GetSubThreadSocketPairFirst() const;
};



#endif