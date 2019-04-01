/*************************************************************************
    > File Name: tcpServer.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 03 Dec 2018 03:44:00 AM PST
 ************************************************************************/

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <sys/types.h>
#include <event.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <json/json.h>
#include "tcpServer.h"
#include "mthread.h"
using namespace std;


void accept_cb(int fd,short event,void* arg){

	cout<<"call tcpServer::acceot cb  fd:"<<fd<<endl;
	TcpServer* p = (TcpServer*)arg;
	static int i = 0;
	if(EV_READ & event){
		struct sockaddr_in cli;
		socklen_t len = sizeof(cli);
		int cfd = accept( fd, (struct sockaddr*)&cli, &len );
		if(-1==cfd){
			cerr<<"accept fail errno:"<<errno<<endl;
			exit(0);
		}
		
		cout<<"recv cfd:"<<i ++<<endl;
		write( p->_pool->getMinFd(), (char*)&cfd, 4 );
	}
}

TcpServer::~TcpServer(){
	delete _pool;
	delete _tcpClient;
	event_base_free(_base);
	close(_listen_fd);
}

TcpServer::TcpServer(const string& ip,short port,int pth_num){
	this->_pth_num = pth_num;//服务器线程的数量

	int listen_fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == listen_fd){
		cerr<<"socket fail errno:"<<errno<<endl;
		exit(0);
	}

	cout<<"_listen_fd:"<<listen_fd<<endl;

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(listen_fd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1 == res){
		cerr<<"bind fail errno:"<<errno<<endl;
		exit(0);
	}

	res = listen(listen_fd,5);
	if(-1 == res){
		cerr<<"listen fail errno:"<<errno<<endl;
		exit(0);
	}

	this->_listen_fd = listen_fd;
	this->_base = event_base_new();
	this->_pool = new ThreadPool(_pth_num);


	this->_tcpClient = new TcpConnect();
	string LBip;
	short LBport;
	sleep(1);
	cout<<"请输入负载均衡服务器的ip地址:";
	cin>>LBip;
	cout<<"请输入负载均衡服务器的端口号:";
	cin>>LBport;
	_tcpClient->Connect(LBip, LBport);
	//构造json对象，给负载均衡服务器发送服务器的ip地址和端口号
	Json::Value val;
	val["ip"] = ip;
	val["port"] = port;
	_tcpClient->Send( val.toStyledString() );
	cout<<"已经将消息发送给负载均衡服务器：ip = "<<ip<<",port = "<<port<<endl;

	struct event* listen_event = event_new(_base, _listen_fd, EV_READ|EV_PERSIST, accept_cb, this);
	event_add(listen_event, NULL);
	event_base_dispatch( _base );
	event_free( listen_event );
}



