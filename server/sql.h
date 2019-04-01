/*************************************************************************
    > File Name: sql.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 04:57:27 AM PST
 ************************************************************************/

#ifndef __SQL_H__
#define __SQL_H__
#include <mysql/mysql.h>
#include <string>
using namespace std;

class Mysql{
private:
	MYSQL* _mpcon;
	MYSQL_RES* _mp_res;
	MYSQL_ROW _mp_row;

public:
	Mysql(const char* server="127.0.0.1",const char* name="root",const char* pw="111111",const char* db="custom");
	~Mysql();

	bool addUser(char* name, char* pw);
	bool isExist(char* name, char* pw);
	bool Search(char* id);
};








#endif

