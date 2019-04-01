/*************************************************************************
    > File Name: worker.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:09:13 PM PST
 ************************************************************************/


#include "worker.h"

Worker::Worker(){
	_selectSer = new selectSerThread();
}

Worker::~Worker(){
	delete _selectSer;
}

void Worker::menu(){
	cout<<"=================="<<endl;
	cout<<"===== 1.插入 ====="<<endl;
	cout<<"===== 2.删除 ====="<<endl;
	cout<<"===== 3.更新 ====="<<endl;
	cout<<"===== 4.查找 ====="<<endl;
	cout<<"===== 5.退出 ====="<<endl;
	cout<<"=================="<<endl;
}

void Worker::run(){
	cout<<"call Worker::run()"<<endl;
	startPthread();
}

void Worker::startPthread(){
	cout<<"call Worker::StartPthread()!"<<endl;
	pthread_t id;
	pthread_create(&id, NULL, Worker::recvFromWorker, _selectSer);
}


void Worker::Insert(){
	cout<<"=====this is Worker::Insert() interface====="<<endl;
	string name,id;
	cout<<"please input the tourist's name:";
	cin>>name;
	cout<<"please input the tourist's id:";
	cin>>id;

	Json::Value val;
	val["type"] = EN_INSERT;
	val["name"] = name.c_str();
	val["id"] = id.c_str();
	WorkSer::getWorkSer()->sendToWorkSer(val.toStyledString());
}
void Worker::Delete(){}
void Worker::Update(){}
void Worker::Search(){}
void Worker::Exit(){}
