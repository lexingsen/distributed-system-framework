/*************************************************************************
    > File Name: tcpServer.cpp
    > Author: Li Si cheng
    > Mail: lexingsen@163.com 
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
#include "logger.h"

TcpServer::TcpServer(const std::string& ip, unsigned short port){
	this->m_ip = ip;
	this->m_port = port;
	m_listenFd = socket(AF_INET,SOCK_STREAM,0);
	if (-1 == m_listenFd) {
		LOG_FUNC_MSG("socket()", errnoMap[errno]);
		return;
	}

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(m_port);
	ser.sin_addr.s_addr = inet_addr(m_ip.c_str());

	if(-1 == bind(m_listenFd, (struct sockaddr*)&ser, sizeof(ser))){
		LOG_FUNC_MSG("bind()", errnoMap[errno]);
		return;
	}

	if (-1 == listen(m_listenFd,5)) {
		LOG_FUNC_MSG("listen()", errnoMap[errno]);
		return;
	}
}

int TcpServer::Accept(){
	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);
	int cli_fd = accept(m_listenFd, (struct sockaddr*)&cli, &len);
	if (cli_fd == -1) {
		LOG_FUNC_MSG("accept()", errnoMap[errno]);
		return -1;
	}
	return cli_fd;
}



int TcpServer::Recv(int fd, std::string& str){
	char buf[128] = {0};
	int n = recv(fd,buf,127,0);
	str = buf;
	return n;
}





int TcpServer::Send(int fd,const std::string& msg) {
	int n = send(fd, msg.c_str(), strlen(msg.c_str()),0);
	return n;
}

int TcpServer::getListenFd() const {
	return m_listenFd;
}

unsigned short TcpServer::getPort() const {
	return m_port;
}

std::string TcpServer::getIp() const {
	return m_ip;
}

