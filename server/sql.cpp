/*************************************************************************
    > File Name: sql.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 04:03:53 PM PST
 ************************************************************************/

#include "sql.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <mysql/mysql.h>
#include <errno.h>
#include <cstdlib>
using namespace std;


Mysql::Mysql(const char* server,const char* name,const char* pw,const char* db){
	_mpcon = mysql_init((MYSQL*)0);
	if(!mysql_real_connect(_mpcon, server, name, pw, db, 3306, NULL, 0)){
		cerr<<"mysql connect fail!errno:"<<errno<<endl;
		exit(0);
	}

	//用于在服务器上显示成功连接上mysql对应的database
	/*
	char str[100] = "connect mysql db=";
	strcat(str,db);
	strcat(str," success!");
	cout<<str<<endl;
	*/
}


Mysql::~Mysql(){
	mysql_close(_mpcon);
	mysql_free_result(_mp_res);
}



bool Mysql::isExist(char* name,char* pw){
	cout<<"Mysql::isExist call!"<<endl;
	if(NULL==name || NULL==pw)return false;

	name[strlen(name)-1] = '\0';
	pw[strlen(pw)-1] = '\0';

	char cmd[128] = {0};
	sprintf(cmd,"select * from user where name='%s' and pw='%s';",name,pw);

	cout<<"sql语句:"<<cmd<<endl;
	if(mysql_query(_mpcon, cmd)){
		cout<<"mysql_query fail!errno="<<errno<<endl;
	}
	_mp_res = mysql_store_result(_mpcon);
	_mp_row = mysql_fetch_row(_mp_res);
	/*
	while(_mp_row!=NULL){
		cout<<_mp_row[0]<<_mp_row[1]<<endl;
		_mp_row = mysql_fetch_row(_mp_res);
	}
	*/
	if(_mp_row!=NULL){
		return true;
	}
	else{
		return false;
	}
}




bool Mysql::addUser(char* name, char* pw){
	cout<<"Mysql::addUser call!"<<endl;
	if(NULL==name || NULL==pw)return false;
	name[strlen(name)-1] = '\0';
	pw[strlen(pw)-1] = '\0';


	char cmd[100];
	sprintf(cmd,"select * from user where name=%s;",name);
	mysql_query(_mpcon, cmd);
	_mp_res = mysql_store_result(_mpcon);
	_mp_row = mysql_fetch_row(_mp_res);
	if(_mp_row!=NULL)
		return false;

	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"insert into user values('%s','%s');",name,pw);

	cout<<"sql语句:"<<cmd<<endl;

	if(0==mysql_query(_mpcon,cmd))
		return true;
	else
		return false;
}

bool Mysql::Search(char* id){
	cout<<"call Mysql::Search()!"<<endl;
	id[strlen(id)-1] = '\0';

	char cmd[128] = {0};
	sprintf(cmd,"select * from blacklist where id='%s';",id);

	cout<<"sql语句:"<<cmd<<endl;

	if( mysql_query(_mpcon, cmd) )
		cout<<"查询失败！errno"<<errno<<endl;
	_mp_res = mysql_store_result(_mpcon);

	if(mysql_num_rows(_mp_res) == 0){
		return false;
	}
	else{
		return true;
	}
}
