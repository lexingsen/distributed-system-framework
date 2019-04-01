/*************************************************************************
    > File Name: mthread.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 03 Dec 2018 03:24:43 AM PST
 ************************************************************************/

#include <iostream>
#include <json/json.h>
#include <string>
#include "mthread.h"
#include "control.h"

using namespace std;

void* task(void* arg);
Mthread::Mthread(){
	_control = new Control();
	if( socketpair(AF_UNIX,SOCK_STREAM,0,fd_main)==-1 )
		cerr<<"创建socketpair失败!errno = "<<errno<<endl;
	pthread_create(&_id, NULL, task, this);
}

Mthread::~Mthread(){
	event_base_free(_base);
	delete _control;
}



void io_cb(int fd,short event,void* arg){
	cout<<"io_cb call,客户端文件描述符为:"<<fd<<endl;
	Mthread* mth = static_cast<Mthread*>(arg);
	char buff[128] = {0};
	cout<<"====recv io_data start===="<<endl;
	if(0>=recv(fd,buff,127,0)){
		cout<<"客户端下线，fd = "<<fd<<endl;
		close(fd);
		return;
	}
	cout<<"io data:"<<buff<<endl;
 	cout<<"====recv io_data end===="<<endl;

	string str( buff );
	Json::Value val;
	Json::Reader read;

	if(!read.parse(str, val)){
		cout<<"converse json object fail!";
		return;
	}
	cout<<"string转换成json格式数据成功，即将将数据发给视图层进行处理!"<<endl;
	cout<<"====将io信息发送给视图层进行处理===="<<endl;

	mth->_control->process(fd,val);
	cout<<"====io信息处理完成===="<<endl;
}


//主线程发给子线程客户端文件描述符(accept到的文件描述符)的回调函数
void fd_cb(int fd,short event,void* arg){
	cout<<"mthread::fd_cb call"<<endl;	
	Mthread* mth = static_cast<Mthread*>(arg);
	int cfd = 0;
	if(0>=recv(fd,&cfd,4,0)){
		cerr<<"recv fail errno:"<<errno<<endl;
		exit(0);
	}
	cout<<"recv ok"<<endl;
	//此时服务器业务线程已经收到主线程发送来的客户端文件描述符


	//创建处理客户端业务的事件处理器，io_cb是具体处理事件的回调函数
	struct event* io_event = event_new(mth->_base, cfd, EV_READ|EV_PERSIST, io_cb, mth);
	if(NULL == io_event){
		cerr<<"event_new fail errno:"<<errno<<endl;
		exit(0);
	}
	event_add(io_event,NULL);

	//一个子线程可能同时处理对多个客户端进行服务
	mth->_event_map.insert( make_pair(cfd,io_event) );
}


void* task(void* arg){
	Mthread* mth = static_cast<Mthread*>(arg);
	mth->_base = event_init();//初始化libevent  

	//创建一个具体事件处理器 fd_main[1]是主线程socketpair端的文件描述符
	struct event* pipe_event = event_new(mth->_base, mth->fd_main[1], EV_READ|EV_PERSIST, fd_cb, mth);
	
	cout<<"fd_main[1]:"<<mth->fd_main[1]<<endl;

	if(NULL==pipe_event){
		cerr<<"创建"<<errno<<endl;
		exit(0);
	}
	event_add(pipe_event,NULL);
	event_base_dispatch(mth->_base);
}

