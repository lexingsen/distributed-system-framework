/*************************************************************************
    > File Name: control.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 03 Dec 2018 04:41:37 AM PST
 ************************************************************************/

#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <map>
#include <json/json.h>
#include "view.h"
#include "public.h"
using namespace std;

class Control{
private:
	map<int,view*> _modelMap;//model
public:
	Control();
	~Control();

	void process(int fd,Json::Value& val);
};



#endif

