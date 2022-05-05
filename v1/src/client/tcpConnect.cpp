/*************************************************************************
    > File Name: tcpConnect.cpp
    > Author: Li Si cheng
    > Mail: lexingsen@163.com 
    > Created Time: Mon 17 Dec 2018 06:08:07 PM PST
 ************************************************************************/
#include <unistd.h>
#include "tcpConnect.h"
#include "logger.h"

int TcpConnect::getConnectFd() const {
	return m_connectFd;
}

uint16_t TcpConnect::getPort() const {
	return m_port;
}

std::string TcpConnect::getIp() const {
	return m_ip;
}

int TcpConnect::Connect(const std::string& ip, unsigned short port){
	this->m_port = port;
	this->m_ip = ip;

	m_connectFd = socket(AF_INET,SOCK_STREAM,0);
	if (m_connectFd == -1){
		LOG_FUNC_MSG("socket()", errnoMap[errno]);
		return -1;
	}

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(m_port);
	ser.sin_addr.s_addr = inet_addr(m_ip.c_str());

	if (-1==connect(m_connectFd,(struct sockaddr*)&ser,sizeof(ser))) {
		LOG_FUNC_MSG("connect()", errnoMap[errno]);
		return -1;
	}
	return m_connectFd;
}

TcpConnect::~TcpConnect(){
	close(m_connectFd);
}
int TcpConnect::Send(const std::string& msg) {
	int n = send(m_connectFd, msg.c_str(),strlen(msg.c_str()),0);
	return n;
}
int TcpConnect::Recv(std::string& msg){
	char buf[128] = {0};
	int n = recv(m_connectFd,buf,127,0);
	msg = buf;
	return n;
}
