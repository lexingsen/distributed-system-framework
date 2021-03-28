/*************************************************************************
    > File Name: SubModule.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:09:13 PM PST
 ************************************************************************/


#include "subModule.h"

SubModule::SubModule(){
	m_informationCollectorThread = new InformationCollectorServerThread();
}

SubModule::~SubModule(){
	delete m_informationCollectorThread;
}

void SubModule::menu(){
	cout<<"=================="<<endl;
	cout<<"===== 1.插入 ====="<<endl;
	cout<<"===== 2.删除 ====="<<endl;
	cout<<"===== 3.更新 ====="<<endl;
	cout<<"===== 4.查找 ====="<<endl;
	cout<<"===== 5.退出 ====="<<endl;
	cout<<"=================="<<endl;
}


void SubModule::startSuModuleThread() {
	LOG_FUNC_TRACE();
	pthread_t tid;
	pthread_create(&tid, nullptr, SubModule::recvFromSubModule, m_informationCollectorThread);
}


void SubModule::Insert(){
	cout<<"=====this is SubModule::Insert() interface====="<<endl;
	string name,id;
	cout<<"please input the tourist's name:";
	cin>>name;
	cout<<"please input the tourist's id:";
	cin>>id;

	Json::Value val;
	val["type"] = EN_INSERT;
	val["name"] = name.c_str();
	val["id"] = id.c_str();
	Transfer::getInstance()->sendToMainSer(val.toStyledString());
}

void SubModule::Delete(){}
void SubModule::Update(){}
void SubModule::Search(){}
void SubModule::Exit(){}
