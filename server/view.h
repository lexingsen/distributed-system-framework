/*************************************************************************
    > File Name: view.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 03 Dec 2018 07:36:30 AM PST
 ************************************************************************/

#ifndef __VIEW_H__
#define __VIEW_H__
#include "public.h"
#include "sql.h"
#include <json/json.h>
using namespace Json;

//事物处理的抽象类提供统一的接口      处理具体业务的子类中必须实现纯虚函数

class view{
public:
	virtual void process(int cli_fd, Value& val)=0;//处理客户套接字cli_fd上的消息     被封装到Json::Value val中

	Mysql* _sql;
};


class view_login:public view{
public:
	view_login();
	~view_login();
	void process(int cli_fd,Value& val);

};

class view_register:public view{
public:
	view_register();
	~view_register();
	void process(int cli_fd,Value& val);	
};

class view_insert:public view{
public:
	view_insert();
	~view_insert();
	void process(int cli_fd,Value& val);
	
};

class view_delete:public view{
public:
	view_delete();
	~view_delete();
	void process(int cli_fd,Value& val);
};

class view_search:public view{
public:
	view_search();
	~view_search();
	void process(int cli_fd,Value& val);
};

class view_update:public view{
public:
	view_update();
	~view_update();
	void process(int cli_fd,Value& val);
};

class view_selecter:public view{
public:
	view_selecter();
	~view_selecter();
	void process(int cli_fd,Value& val);
};


#endif
