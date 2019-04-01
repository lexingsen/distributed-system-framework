/*************************************************************************
    > File Name: tcpServer.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Sun 25 Nov 2018 04:09:00 AM PST
 ************************************************************************/

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include <string>

using namespace std;

class TcpServer{
public:
	TcpServer(const string& ip,short port);
	int Accept();

	int Send(int fd,const string& message);
	int Recv(int fd,string& str);
	int getListenFd();
	short getPort();
	string getIp();
private:
	int _listenFd;
	short _port;
	string  _ip;
};

#endif
