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
	cout<<"===== 1.增加黑名单成员 ====="<<endl;
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
	string name,id_card;
	cout << "please input the tourist's name:";
	cin >> name;
	cout << "please input the tourist's id_card:";
	cin >> id_card;

	Json::Value val;
	static int blacklistCnt = 1;
	val["type"] = EN_INSERT;
	val["id"] = blacklistCnt ++;
	val["name"] = name.c_str();
	val["id_card"] = id_card.c_str();
	Transfer::getInstance()->sendToMainSer(val.toStyledString());
}

void SubModule::Delete(){}
void SubModule::Update(){}
void SubModule::Search(){}
void SubModule::Exit(){}
