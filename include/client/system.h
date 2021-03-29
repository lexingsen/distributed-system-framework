/*************************************************************************
    > File Name: system.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 25 Nov 2018 05:51:30 AM PST
 ************************************************************************/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include <json/json.h>
#include "logger.h"
#include "subModule.h"

using namespace std;

class System {
public:
	System();
	~System();

	void menu();
	void Register();
	void Login();
	void Exit();
private:
	SubModule* m_subModule;
};

#endif
