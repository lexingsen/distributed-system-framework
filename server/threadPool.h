/*************************************************************************
    > File Name: threadPool.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 16 Dec 2018 11:50:42 PM PST
 ************************************************************************/

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "mthread.h"
#include <vector>

class ThreadPool{
public:
	ThreadPool(int num);
	~ThreadPool();
	int getMinFd();
	//获取当前压力最小的线程，返回值为压力最小线程的socketpair的fd[0]
private:
	int _num;//线程池中的线程数量 
	vector<Mthread*> _th;
};



#endif

