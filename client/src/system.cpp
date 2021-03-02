/*************************************************************************
    > File Name: system.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:07:58 PM PST
 ************************************************************************/

#include "system.h"
#include "workSer.h"
#include "public.h"

typedef void (Worker::*PFUNC)();
typedef struct FuncMap1{
	int choice;
	PFUNC pfunc;
}FuncMap1;

FuncMap1 funcMap1[] = {
	{EN_INSERT,&Worker::Insert},
	{EN_DELETE,&Worker::Delete},
	{EN_UPDATE,&Worker::Update},
	{EN_SEARCH,&Worker::Search}
};

System::System(){_work = new Worker();}
System::~System(){delete _work;}

void System::menu(){
	cout<<"====================="<<endl;
	cout<<"====== 5.注册 ======="<<endl;
	cout<<"====== 6.登录 ======="<<endl;
	cout<<"====== 7.退出 ======="<<endl;
	cout<<"====================="<<endl;
}

void System::Login(){
	/*
	string ip;
	cout<<"please input the server ip address:";
	cin>>ip;
	getchar();

	short port;
	cout<<"please input the server port:";
	cin>>port;
	getchar();
	*/
	cout<<"=====this is login user interface====="<<endl;
	string name,pw;
	cout<<"please input your name:";
	cin>>name;
	cout<<"please input your password:";
	cin>>pw;

	Json::Value val;
	val["type"] = EN_LOGIN;
	val["name"] = name.c_str();
	val["pw"] = pw.c_str();

	//使用默认的ip和port进行发送
	WorkSer::getWorkSer()->sendToWorkSer(val.toStyledString());
	cout<<"已经将登录信息发送给主服务器!请等待..."<<endl;

	//使用默认的ip和port进行发送
	string recvMessage;
	WorkSer::getWorkSer()->recvFromWorkSer(recvMessage);
	
	cout<<"服务器:"<<recvMessage;
	
	Json::Reader read;
	Json::Value res;
	if(!read.parse(recvMessage,res)){
		cout<<"converse json object fail!errno"<<errno<<endl;
		return;
	}

	//去掉换行符
	char message[100] = {0};
	strcat(message,res["message"].toStyledString().c_str());
	message[strlen(message)-1] = '\0';

	if(strcmp(message,"\"login success!\"") == 0){
		_work->run();
		_work->menu();

		int  choice;
		cout<<"please input your choice:";
		cin>>choice;
		getchar();
		for(int i=0;i<sizeof(funcMap1)/sizeof(funcMap1[0]);++i){
			if(choice == funcMap1[i].choice){
				(_work->*funcMap1[i].pfunc)();
			}
		}
	}
}

void System::Register(){
	/*
	string ip;
	cout<<"please input the server ip address:";
	cin>>ip;

	short port;
	cout<<"please input the server port:";
	cin>>port;
	*/
	cout<<"=====this is register user interface====="<<endl;
	string name,pw;
	cout<<"please input your name:";
	cin>>name;
	cout<<"please input your password:";
	cin>>pw;

	Json::Value val;
	val["type"] = EN_REGISTER;
	val["name"] = name.c_str();
	val["pw"] = pw.c_str();

	//使用默认的ip和port进行发送
	WorkSer::getWorkSer()->sendToWorkSer(val.toStyledString());

	cout<<"已经将注册信息发送给主服务器!请等待"<<endl;
	string recvMessage;
	//使用默认的ip和port进行发送
	WorkSer::getWorkSer()->recvFromWorkSer(recvMessage);
	cout<<"服务器:"<<recvMessage<<endl;

	Json::Reader read;
	Json::Value res;
	if(!read.parse(recvMessage,res)){
		cout<<"converse json object fail!errno"<<errno<<endl;
		return;
	}

	//去掉换行符
	char message[100] = {0};
	strcat(message,res["message"].toStyledString().c_str());
	message[strlen(message)-1] = '\0';

	if(strcmp(message,"\"register success!\"") == 0){
		_work->run();
		_work->menu();

		int choice;
		cout<<"please input your choice:";
		cin>>choice;
		getchar();
		for(int i=0;i<sizeof(funcMap1)/sizeof(funcMap1[0]);++i){
			if(choice == funcMap1[i].choice){
				(_work->*funcMap1[i].pfunc)();
			}
		}
	}
}

void System::Exit(){return;}
