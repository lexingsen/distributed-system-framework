/*************************************************************************
    > File Name: control.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 03 Dec 2018 06:48:29 AM PST
 ************************************************************************/

#include "control.h"
#include "public.h"
#include <json/json.h>
#include <errno.h>
#include <stdlib.h>
#include <map>
using namespace std;


Control::Control(){
	_modelMap.insert(make_pair(EN_LOGIN,    new view_login()));
	_modelMap.insert(make_pair(EN_REGISTER, new view_register()));
	_modelMap.insert(make_pair(EN_SELECT,   new view_selecter()));
	_modelMap.insert(make_pair(EN_INSERT,   new view_insert()));
	_modelMap.insert(make_pair(EN_UPDATE,   new view_update()));
	_modelMap.insert(make_pair(EN_DELETE,   new view_delete()));
	_modelMap.insert(make_pair(EN_SEARCH,   new view_search()));
}

Control::~Control(){
	//cout<<"call Control::~Control() "<<endl;
	map<int,view*>::iterator it = _modelMap.begin();
	for(;it!=_modelMap.end();++it){
		delete (*it).second;
	}
}

void Control::process(int fd,Json::Value& val){
	//cout<<"call Control::process!"<<endl;
	_modelMap[val["type"].asInt()]->process(fd,val);
}
