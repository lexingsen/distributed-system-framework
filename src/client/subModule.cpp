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

SubModule::~SubModule() {
	delete m_informationCollectorThread;
}

void SubModule::menu() {
	std::cout << "****************************************************************" << std::endl;
	std::cout << "****************************************************************" << std::endl;
	std::cout << "***************** welcome to submodule menu ui *****************" << std::endl;
	std::cout << "*****************       (4).增加黑名单成员       *****************" << std::endl;
	std::cout << "*****************       (5).删除黑名单成员       *****************" << std::endl;
	std::cout << "*****************       (6).更新单成员       *****************" << std::endl;
	std::cout << "*****************       (7).查找黑名单成员       *****************" << std::endl;
	std::cout << "****************************************************************" << std::endl;
	std::cout << "****************************************************************" << std::endl;
}


void SubModule::startSuModuleThread() {
	LOG_FUNC_TRACE();
	pthread_t tid;
	pthread_create(&tid, nullptr, SubModule::recvFromSubModule, m_informationCollectorThread);
}


void SubModule::Insert(){
	std::cout << "=====this is SubModule::Insert() interface=====" << std::endl;
	std::string name,id_card;
	std::cout << "please input the tourist's name:";
	std::cin >> name;
	std::cout << "please input the tourist's id_card:";
	std::cin >> id_card;

	Json::Value val;
	val["type"] = EN_INSERT;
	val["name"] = name.c_str();
	val["id_card"] = id_card.c_str();
	Transfer::getInstance()->sendToMainSer(val.toStyledString());
	return;
}

void SubModule::Delete(){}
void SubModule::Update(){}
void SubModule::Search(){}
void SubModule::Exit(){}
