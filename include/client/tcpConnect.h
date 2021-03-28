/*************************************************************************
    > File Name: tcpConnect.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 25 Nov 2018 04:59:03 AM PST
 ************************************************************************/

#ifndef __TCPCONNECT_H__
#define __TCPCONNECT_H__

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cassert>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>


class TcpConnect {
private:
	int m_connectFd;
	std::string m_ip;
	uint16_t m_port;
public:
	int getConnectFd() const;
	uint16_t getPort() const;
	std::string getIp() const;


	int Connect(const std::string& ip, unsigned short port);
	~TcpConnect();
	int Send(const std::string& msg);
	int Recv(std::string& msg);
};
#endif


