
#ifndef __WORK_H__
#define __WORK_H__
#include "selectSerThread.h"
#include <iostream>
#include <json/json.h>
#include <pthread.h>
#include "workSer.h"
#include "public.h"


class Worker{
public:

	Worker();
	~Worker();
	void menu();
	void run();
	void startPthread();
	void Delete();
	void Insert();
	void Update();
	void Search();
	void Exit();


	static void* recvFromWorker(void* arg){
		cout<<"call static viod recvFromWorker()"<<endl;
		selectSerThread* selectSer = static_cast<selectSerThread*>(arg);
		while(1){
			string str;
			if(WorkSer::getWorkSer()->recvFromWorkSer(str)){

				cout<<"服务器消息:"<<str;

				Json::Value val;
				Json::Reader read;

				if(!read.parse(str ,val)){
					cerr<<"read buff fail!errno:"<<errno<<endl;
					continue;
				}

				if(val["type"].asInt()==EN_SELECT && val["fd"]!=-1){
					cout<<"即将发送数据给信息采集器!"<<endl;
					int fd = val["fd"].asInt();
					string mes = val["message"].asString();
					selectSer->sendSelect(fd, mes);
				}

				else{
					cout<<val["message"].asString()<<endl;
				}
			}
		}
	}
private:
	selectSerThread* _selectSer;// 信息采集机的服务器
};

#endif
