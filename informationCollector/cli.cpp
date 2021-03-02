/*************************************************************************
    > File Name: cil.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Fri 21 Dec 2018 08:47:55 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <string>
using namespace std;

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd==-1){
		cerr<<"socket() fail!errno:"<<errno<<endl;
		exit(0);
	}

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;

	string ip;
	cout<<"please input selectSer ip address:";
	cin>>ip;

	short port;
	cout<<"please input selectSer port address:";
	cin>>port;
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = inet_addr(ip.c_str());

	if(-1 == connect(sockfd,(struct sockaddr*)&ser,sizeof(ser))){
		cerr<<"connect fail!errno:"<<errno<<endl;
		exit(0);
	}

	string id;
	printf("please input the custom's id:");
	cin>>id;
	send(sockfd,id.c_str(),strlen(id.c_str()),0);

	char buff[128] = {0};
	
	recv(sockfd,buff,127,0);
	printf("%s\n",buff);
	
	return 0;
}
