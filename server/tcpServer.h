/*************************************************************************
    > File Name: tcpServer.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 03 Dec 2018 12:39:47 AM PST
 ************************************************************************/

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdint.h>
#include "threadPool.h"
#include "tcpConnect.h"
using namespace std;



class TcpServer{
public:
	TcpServer(const string& ip,short port,int pth_num);
	~TcpServer();

	ThreadPool* _pool;

private:
	struct event_base* _base;
	TcpConnect* _tcpClient;//作为客户端去连接负载均衡服务器
	int _listen_fd;
	int _pth_num;


	friend void accpet_cb(int fd,short event,void* arg);
	friend void listen_0_cb(int fd,short event,void* arg);
};

#endif
