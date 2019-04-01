/*************************************************************************
    > File Name: threadPool.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 12:16:58 AM PST
 ************************************************************************/

#include "threadPool.h"


ThreadPool::ThreadPool(int num):_num(num){
	for(int i=0;i<_num;++i){
		_th.push_back( new Mthread() );
	}
}

ThreadPool::~ThreadPool(){
	for(int i=_th.size()-1; i>=0; --i){
		delete _th[i];
		_th.pop_back();	
	}
}

int ThreadPool::getMinFd(){
	static size_t Ronbin = 0;
	int pre = _th[Ronbin % _num]->fd_main[0];
	Ronbin ++;

	for(int i=0;i<_th.size();++i)
		cout<< "[" <<_th[i]->_id % 1000 << "]thread's 线程压力大小为:" <<_th[i]->_event_map.size()<<endl;
	return pre;
}
