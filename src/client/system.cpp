/*************************************************************************
    > File Name: system.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:07:58 PM PST
 ************************************************************************/

#include "system.h"
#include "transfer.h"
#include "logger.h"

typedef void (SubModule::*PFUNC)();
typedef struct {
	int type;
	PFUNC pfunc;
} SubModuleHandler;

SubModuleHandler subModuleHandlerMap[] = {
	{EN_INSERT, &SubModule::Insert},
	{EN_DELETE, &SubModule::Delete},
	{EN_UPDATE, &SubModule::Update},
	{EN_SEARCH, &SubModule::Search}
};

System::System(unsigned short port) {
	m_subModule = new SubModule(port);
	m_subModule->startSuModuleThread();
}
System::~System() {
	delete m_subModule;
}

void System::menu() {
	std::cout << "************************************************************" << std::endl;
	std::cout << "****************** welcome to main men ui ******************" << std::endl;
	std::cout << "************************************************************" << std::endl;
	std::cout << "******************      (1).login         ******************" << std::endl;
	std::cout << "******************      (2).register      ******************" << std::endl;
	std::cout << "******************      (3).exit          ******************" << std::endl;
	std::cout << "************************************************************" << std::endl;
	std::cout << "************************************************************" << std::endl;
}

void System::Login() {
	std::cout << "=====this is login user interface=====" << std::endl;
	std::string name, pw;
	std::cout << "please input your name:";
	std::cin >> name;
	std::cout << "please input your password:";
	std::cin >> pw;

	Json::Value val;
	val["type"] = EN_LOGIN;
	val["name"] = name.c_str();
	val["password"] = pw.c_str();


	Transfer::getInstance()->sendToMainSer(val.toStyledString());
	std::string recvMsg;
	Transfer::getInstance()->recvFromMainSer(recvMsg);
	
	
	
	Json::Reader read;
	Json::Value res;
	if(!read.parse(recvMsg, res)){
		LOG_FUNC_MSG("json reader parse fail!", errnoMap[errno]);
		return;
	}

	char buf[BUF_LEN] = {0};
	strcat(buf, res["message"].asCString());
	LOG_SOURCE_MSG("mainServer", buf);

	if (strcmp(buf, "login success!") == 0) {
		m_subModule->menu();
		int type;
		std::cout << "please input your type:";
		std::cin >> type;
		getchar();
		for(int i = 0; i < sizeof(subModuleHandlerMap)/sizeof(SubModuleHandler); ++i){
			if(type == subModuleHandlerMap[i].type) {
				(m_subModule->*subModuleHandlerMap[i].pfunc)();
				break;
			}
		}
	}
	return;
}

void System::Register() {
	LOG_FUNC_TRACE();
	std::cout <<"=====this is register user interface=====" << std::endl;
	std::string name,pw;
	std::cout << "please input your name:";
	std::cin >> name;
	std::cout << "please input your password:";
	std::cin >> pw;

	Json::Value val;
	val["type"] = EN_REGISTER;
	val["name"] = name.c_str();
	val["pw"] = pw.c_str();

	Transfer::getInstance()->sendToMainSer(val.toStyledString());

	std::string recvMsg;
	Transfer::getInstance()->recvFromMainSer(recvMsg);

	Json::Reader read;
	Json::Value res;
	if(!read.parse(recvMsg,res)) {
		LOG_FUNC_MSG("json reader parse fail!", errnoMap[errno]);
		return;
	}

	char buf[BUF_LEN] = {0};
	strcat(buf, res["message"].asCString());

	if(strcmp(buf, "\"register success!\"") == 0){
		LOG_MSG(buf);
	}
	return;
}

void System::Exit() {
	return;
}
