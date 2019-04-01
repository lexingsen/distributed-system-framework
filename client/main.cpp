/*************************************************************************
    > File Name: main.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sat 01 Dec 2018 04:38:56 AM PST
 ************************************************************************/

#include <iostream>
#include "public.h"
#include "system.h"
#include "workSer.h"
#include "selectSerThread.h"
using namespace std;

event_base* selectSerThread::_base = NULL;
map<int, struct event*> selectSerThread::_eventMap;
WorkSer* WorkSer::_workSer = NULL;

typedef void (System::*PFUNC)();
typedef struct{
	int choice;
	PFUNC pfunc;
}FuncMap;

FuncMap funcMap[]={
	{EN_REGISTER,&System::Register},
	{EN_LOGIN,&System::Login}
};


int main(){
	System* s = new System();
	sleep(1);

	while(1){
		s->menu();
		cout<<"please input your choice:";
		int choice;
		cin>>choice;
		getchar();
		int size = sizeof(funcMap)/sizeof(funcMap[0]);
		int i;
		for(i=0;i<size;++i){
			if(choice == funcMap[i].choice){
				(s->*funcMap[i].pfunc)();
			}
		}
		if(i>size)continue;
		
	}

	delete s;
	return 0;
}
