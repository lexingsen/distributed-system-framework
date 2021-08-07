/*
 * @Description: 
 * @Language: 
 * @Author: 
 * @Date: 2021-03-26 01:43:34
 */
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
#include <unistd.h>
#include <json/json.h>
#include "tcpServer.h"
#include "transfer.h"
#include "logger.h"
#include "logger.h"
using namespace std;

class InformationCollectorServerThread {
public:

	/*
	description:监听信息采集器连接的回调事件
	创建处理信息采集器io事件 

	*/	
	static void listenInformationCollectorConnectCallBack(int fd, short event, void* arg){
		LOG_FUNC_TRACE();
		TcpServer* server = static_cast<TcpServer*>(arg);
		int cfd = server->Accept();
		if (-1 == cfd) {
			LOG_FUNC_MSG("server->accept()", errnoMap[errno]);
			return;
		}

		struct event* ev = event_new(m_base, cfd, EV_READ|EV_PERSIST, InformationCollectorServerThread::informationCollectorIOEventCallBack,server);
		if (nullptr == ev) {
			LOG_FUNC_MSG("event_new()", errnoMap[errno]);
			return;
		}
		m_eventMap.insert(make_pair(cfd, ev));
		event_add(ev, nullptr);
	}


	static void informationCollectorIOEventCallBack(int fd, short event, void* arg){
		LOG_FUNC_TRACE();
		TcpServer* server = static_cast<TcpServer*>(arg);
		string msg;
		if (server->Recv(fd, msg) <= 0) {
			LOG("informationCollector client shutdown!");
			event_free(m_eventMap[fd]);
			m_eventMap.erase(fd);
			close(fd);
			return ;
		}
		Json::Value res;
		Json::Reader reader;
		if (-1 == reader.parse(msg, res)) {
			LOG_MSG("json reader parse fail!");
			return;
		}

		Json::Value val;
		val["type"] = EN_INFORMATION_COLLECTOR;
		val["id_card"] = res["id_card"].asCString();
		val["name"] = res["name"].asCString();

		cout<<"selecter data:"<<val;
		cout<<"将信息采器的数据发送给主服务器!"<<endl;
		Transfer::getInstance()->sendToMainSer(val.toStyledString());
		cout<<"信息采集机器的数据发送给主服务器完毕!"<<endl;
	}

	static void* startInformationCollectorServerThread(void* arg){
		LOG_FUNC_TRACE();
		struct event_base* base = static_cast<struct event_base*>(arg);
		event_base_dispatch(base);
	}
	
	InformationCollectorServerThread(unsigned short);
	void sendToInformationCollector(int fd, std::string& msg);


private:
	TcpServer* m_informationCollectorServer;
	static struct event_base* m_base;
	static std::map<int,struct event*> m_eventMap;
};

#endif
