/*************************************************************************
    > File Name: threadPool.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 02 Dec 2018 10:58:41 PM PST
 ************************************************************************/

#ifndef __MTHREAD_H__
#define __MTHREAD_H__
#include <iostream>
#include <map>
#include <event.h>
#include <sys/socket.h>
#include <errno.h>
#include "control.h"
#include <string.h>
#include <stdlib.h>
using namespace std;

class Mthread{
public:
	Mthread();
	~Mthread();

	int fd_main[2];//和主进程通信的socket
	map<int, struct event*> _event_map;
	pthread_t _id;
private:
	struct event_base* _base;
	//每一个线程都有一个事件循环
	//_event_map.size()表示当前线程监听客户端的总数   线程的压力大小
	//每一个客户端文件描述符对应一个事件  保存事件的map表
	

	Control* _control;//控制台

	//处理客户端io信息的回调函数，注册在libevent中
	friend void io_cb(int fd,short event,void* arg);
	friend void fd_cb(int fd,short event,void* arg);


	//在构造函数中调用pthread_create构造线程的线程函数
	friend void* task(void* arg);
};

#endif

