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


int main() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		LOG("socket error!");
		exit(0);
	}

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;

	std::string ip = "";
	std::cout << "please input information collector server ip address:";
	std::cin >> ip;

	short port = -1;
	std::cout << "please input information collector server port:";
	std::cin >> port;
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = inet_addr(ip.c_str());

	if(-1 == connect(sockfd,(struct sockaddr*)&ser, sizeof(ser))) {
		LOG("connect error!");
		exit(0);
	}

	std::string id = "";
  std::cout << "please input the tourist's id:";
	std::cin >> id;
	send(sockfd, id.c_str(), strlen(id.c_str()), 0);

	char buf[128] = {0};
	
	recv(sockfd, buf, 127, 0);
  cout << buf << endl;
	return 0;
}