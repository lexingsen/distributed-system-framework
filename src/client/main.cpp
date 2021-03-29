/*************************************************************************
    > File Name: main.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sat 01 Dec 2018 04:38:56 AM PST
 ************************************************************************/

#include <iostream>
#include "logger.h"
#include "system.h"
#include "transfer.h"
#include "informationCollectorServerThread.h"



typedef void (System::*PFUNC)();
typedef struct{
  int type;	
  PFUNC pfunc;
} SystemHandler;

SystemHandler systemHandlerMap[]={
	{EN_REGISTER,&System::Register},
	{EN_LOGIN,&System::Login}
};


int main() {
	System* s = new System();
	sleep(1);

	for (;;) {
		s->menu();
		std::cout << "please input your type:";
		int type;
		std::cin >> type;
		getchar();
		int size = sizeof(systemHandlerMap)/sizeof(SystemHandler);
		int i;
		for (i = 0; i < size; ++i){
			if(type == systemHandlerMap[i].type){
				(s->*systemHandlerMap[i].pfunc)();
			}
		}
		if(i>size)continue;
		
	}

	delete s;
	return 0;
}
