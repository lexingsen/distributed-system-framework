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

System::System() {
	m_subModule = new SubModule();
	m_subModule->startSuModuleThread();
}
System::~System() {
	delete m_subModule;
}

void System::menu(){
	cout<<"====================="<<endl;
	cout<<"====== 5.注册 ======="<<endl;
	cout<<"====== 6.登录 ======="<<endl;
	cout<<"====== 7.退出 ======="<<endl;
	cout<<"====================="<<endl;
}

void System::Login(){
	std::cout << "=====this is login user interface=====" << std::endl;
	std::string name,pw;
	std::cout << "please input your name:";
	std::cin >> name;
	std::cout << "please input your password:";
	std::cin >> pw;

	Json::Value val;
	val["type"] = EN_LOGIN;
	val["name"] = name.c_str();
	val["password"] = pw.c_str();

	//使用默认的ip和port进行发送
	Transfer::getInstance()->sendToMainSer(val.toStyledString());
	cout<<"已经将登录信息发送给主服务器!请等待..."<<endl;

	//使用默认的ip和port进行发送
	string recvMsg;
	Transfer::getInstance()->recvFromMainSer(recvMsg);
	
	cout<<"服务器:"<<recvMsg;
	
	Json::Reader read;
	Json::Value res;
	if(!read.parse(recvMsg, res)){
		LOG_FUNC_MSG("json reader parse fail!", errnoMap[errno]);
		return;
	}

	//去掉换行符
	char message[128] = {0};
	strcat(message,res["message"].asCString());
	LOG_MSG(message);

	if (strcmp(message,"login success!") == 0){
		m_subModule->menu();
		int type;
		std::cout << "please input your type:";
		std::cin >> type;
		getchar();
		for(int i = 0; i < sizeof(subModuleHandlerMap)/sizeof(SubModuleHandler);++i){
			if(type == subModuleHandlerMap[i].type) {
				(m_subModule->*subModuleHandlerMap[i].pfunc)();
			}
		}
	}
}

void System::Register() {
	LOG_FUNC_TRACE();
	std::cout <<"=====this is register user interface=====" << std::endl;
	std::string name,pw;
	std::cout << "please input your name:";
	std::cin >> name;
	std::cout << "please input your password:";
	cin>>pw;

	Json::Value val;
	val["type"] = EN_REGISTER;
	val["name"] = name.c_str();
	val["pw"] = pw.c_str();

	//使用默认的ip和port进行发送
	Transfer::getInstance()->sendToMainSer(val.toStyledString());

	cout<<"已经将注册信息发送给主服务器!请等待"<<endl;
	std::string recvMessage;
	//使用默认的ip和port进行发送
	Transfer::getInstance()->recvFromMainSer(recvMessage);
	cout<<"服务器:"<<recvMessage<<endl;

	Json::Reader read;
	Json::Value res;
	if(!read.parse(recvMessage,res)){
		LOG_FUNC_MSG("json reader parse fail!", errnoMap[errno]);
		return;
	}

	//去掉换行符
	char message[128] = {0};
	strcat(message,res["message"].toStyledString().c_str());
	message[strlen(message)-1] = '\0';

	if(strcmp(message,"\"register success!\"") == 0){
		m_subModule->menu();

		int type;
		cout<<"please input your type:";
		std::cin >> type;
		getchar();
		for(int i = 0; i < sizeof(subModuleHandlerMap)/sizeof(SubModuleHandler); ++i) {
			if(type == subModuleHandlerMap[i].type){
				(m_subModule->*subModuleHandlerMap[i].pfunc)();
			}
		}
	}
}

void System::Exit(){return;}
