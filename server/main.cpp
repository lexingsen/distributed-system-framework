/*************************************************************************
    > File Name: main.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 02 Dec 2018 10:38:22 PM PST
 ************************************************************************/

#include "tcpServer.h"

int main(){
	short port;;
	cout<<"please input port:";
	cin>>port;
	string str("127.0.0.1");
	TcpServer ser(str,port,4);
	return 0;
}
