/*************************************************************************
    > File Name: selecterSer.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 25 Nov 2018 06:03:34 AM PST
 ************************************************************************/

#ifndef __SELECTSERTHREAD_H__
#define __SELECTSERTHREAD_H__

#include <iostream>
#include <pthread.h>
#include <string>
#include <map>
#include <event.h>
#include <json/json.h>
#include "tcpServer.h"
#include "workSer.h"
#include "public.h"
using namespace std;

class selectSerThread{
public:

	static void listen_cb(int fd,short event,void* arg){
		TcpServer* server = static_cast<TcpServer*>(arg);
		int cliFd = server->Accept();
		if(-1 == cliFd){
			cerr<<"selectSerThread::listen_cb() call!,select cli accept fail;errno:"<<errno<<endl;
			return;
		}

		struct event* cliEvent = event_new(_base, cliFd,EV_READ|EV_PERSIST,selectSerThread::io_cb,server);
		if(cliEvent == NULL){
			cerr<<"select ser thread cli event new fail;errno"<<errno<<endl;
			return;
		}
		_eventMap.insert(make_pair(cliFd,cliEvent));
		event_add(cliEvent,NULL);
	}


	static void io_cb(int fd,short event,void* arg){
		TcpServer* server = static_cast<TcpServer*>(arg);
		string id;
		if(server->Recv(fd,id)<=0){
			cerr<<"select cli shut down;errno:"<<errno<<endl;
			event_free(_eventMap[fd]);
			_eventMap.erase(fd);
			close(fd);
			return ;
		}

		Json::Value val;
		val["type"] = EN_SELECT;
		val["fd"] = fd;
		val["message"] = id.c_str();

		cout<<"selecter data:"<<val;
		cout<<"将信息采器的数据发送给主服务器!"<<endl;
		WorkSer::getWorkSer()->sendToWorkSer(val.toStyledString());
		cout<<"信息采集机器的数据发送给主服务器完毕!"<<endl;
	}

	static void* selectThreadRun(void* arg){
		//libevent开始进行监听
		cout<<"libevent 开始进行监听信息采集器的消息！"<<endl;
		struct event_base* base = static_cast<struct event_base*>(arg);
		event_base_dispatch(base);
	}
	
	selectSerThread();
	void sendSelect(int fd,string& str);


private:
	TcpServer* _selectSer;
	static struct event_base* _base;
	static map<int,struct event*> _eventMap;
};

#endif
