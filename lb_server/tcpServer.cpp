/*************************************************************************
    > File Name: tcpServer.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:09:04 PM PST
 ************************************************************************/

#include "tcpServer.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
using namespace std;

TcpServer::TcpServer(const string& ip,short port){
	this->_ip = ip;
	this->_port = port;
	_listenFd = socket(AF_INET,SOCK_STREAM,0);
	if(-1==_listenFd){
		cerr<<"listen fail errno:"<<errno<<endl;
		return;
	}

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(_port);
	ser.sin_addr.s_addr = inet_addr(_ip.c_str());

	if(-1 == bind(_listenFd, (struct sockaddr*)&ser, sizeof(ser))){
		cerr<<"bind fail!errno:"<<errno<<endl;
		return;
	}

	if(-1 == listen(_listenFd,5)){
		cerr<<"listen fail!errno:"<<errno<<endl;
		return;
	}
}

int TcpServer::Accept(){
	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);
	int cli_fd = accept(_listenFd, (struct sockaddr*)&cli, &len);
	if(cli_fd == -1){
		cerr<<"accept fail!errno:"<<errno<<endl;
		return -1;
	}
	return cli_fd;
}

int TcpServer::Recv(int fd,string& str){
	char buff[128] = {0};
	int n = recv(fd,buff,127,0);
	str = buff;
	return n;
}

int TcpServer::Send(int fd,const string& message){
	cout<<"call TcpServer::Send() fd="<<fd<<endl;
	int n = send(fd,message.c_str(),strlen(message.c_str()),0);
	return n;
}

int TcpServer::getListenFd(){return _listenFd;}
short TcpServer::getPort(){return _port;}
string TcpServer::getIp(){return _ip;}

