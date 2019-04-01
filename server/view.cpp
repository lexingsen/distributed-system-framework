/*************************************************************************
    > File Name: view.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 03:58:22 PM PST
 ************************************************************************/

#include "view.h"
#include "sql.h"
#include <sys/socket.h>
#include <cstring>
#include <iostream>
using namespace std;

view_login::view_login(){_sql = new Mysql();}
view_login::~view_login(){delete _sql;}
void view_login::process(int cli_fd,Value& val){
	Value res;
	res["fd"] = -1;
	cout<<"wiew_login 开始处理客户端数据!"<<endl;
	
	if(_sql->isExist((char*)val["name"].toStyledString().c_str(), (char*)val["pw"].toStyledString().c_str()))
		res["message"] = "login success!";
	else
		res["message"] = "login fail!";

	cout<<"对数据库进行查询此用户信息结束!"<<endl;

	cout<<val<<endl;

	send(cli_fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
}

view_register::view_register(){_sql = new Mysql();}
view_register::~view_register(){delete _sql;}
void view_register::process(int cli_fd,Value& val){
	cout<<"view_register开始处理客户端数据!"<<endl;
	Value res;
	val["fd"] = -1;
	if(_sql->addUser((char*)val["name"].toStyledString().c_str(), (char*)val["pw"].toStyledString().c_str()))
		res["message"] = "register success!";
	else
		res["message"] = "register fail!";
	send(cli_fd,res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
}



view_insert::view_insert(){_sql = new Mysql();}
view_insert::~view_insert(){delete _sql;}
void view_insert::process(int cli_fd,Value& val){}


view_delete::view_delete(){_sql = new Mysql();}
view_delete::~view_delete(){delete _sql;}
void view_delete::process(int cli_fd,Value& val){}

view_update::view_update(){_sql = new Mysql();}
view_update::~view_update(){delete _sql;}
void view_update::process(int cli_fd,Value& val){}

view_search::view_search(){_sql = new Mysql();}
view_search::~view_search(){delete _sql;}
void view_search::process(int cli_fd,Value& val){
	cout<<"vew_search::process()开始处理数据"<<endl;
	Value res;
	res["fd"] = -1;
}

view_selecter::view_selecter(){_sql = new Mysql();}
view_selecter::~view_selecter(){delete _sql;}

void view_selecter::process(int cli_fd,Value& val){
	cout<<"view_selecter::process() 开始处理数据"<<endl;
	Value res;
	res["fd"] = val["fd"];
	res["type"] = EN_SELECT;

	if(_sql->Search( (char*)val["message"].toStyledString().c_str() ))
		res["message"] = "exist!";
	else
		res["message"] = "no exist!";
	
	cout<<"数据在数据库中查询完成！"<<endl;
	send(cli_fd, res.toStyledString().c_str(), strlen(res.toStyledString().c_str()), 0);
	cout<<"已经将服务器数据发送给客户端！"<<endl;
}
