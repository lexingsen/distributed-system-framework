/*************************************************************************
    > File Name: tcpConnect.cpp
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Mon 17 Dec 2018 06:08:07 PM PST
 ************************************************************************/

#include "tcpConnect.h"

int TcpConnect::getConnectFd(){
	return _connectFd;
}

uint16_t TcpConnect::getPort(){
	return _port;
}

string TcpConnect::getIp(){
	return _ip;
}

int TcpConnect::Connect(const string& ip,short  port){
	this->_port = port;
	this->_ip = ip;

	_connectFd = socket(AF_INET,SOCK_STREAM,0);
	if(_connectFd == -1){
		cerr<<"socket fail;errno:"<<errno<<endl;
		return -1;
	}

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(_port);
	ser.sin_addr.s_addr = inet_addr(_ip.c_str());

	if(-1==connect(_connectFd,(struct sockaddr*)&ser,sizeof(ser))){
		cerr<<"call connect fail errno:"<<errno<<endl;
		return -1;
	}
	return _connectFd;
}

TcpConnect::~TcpConnect(){
	close(_connectFd);
}
int TcpConnect::Send(const string& message){
	cout<<"call TcpConnect::Send()!"<<endl;
	int n = send(_connectFd, message.c_str(),strlen(message.c_str()),0);
	return n;
}
int TcpConnect::Recv(string& str){
	char buff[128] = {0};
	int n = recv(_connectFd,buff,127,0);
	str = buff;
	return n;
}
