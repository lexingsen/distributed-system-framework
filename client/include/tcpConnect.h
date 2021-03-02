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
using namespace std;


class TcpConnect{
private:
	int _connectFd;
	string _ip;
	uint16_t _port;
public:
	int getConnectFd();
	uint16_t getPort();
	string getIp();


	int Connect(const string& ip,short port);
	~TcpConnect();
	int Send(const string& message);
	int Recv(string& str);
};

#endif


