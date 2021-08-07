/*************************************************************************
    > File Name: informationCollectorClient.cpp
    > Author: lexingsen
    > Mail: lexingsen@qq.com 
    > Created Time: Fri 21 Dec 2018 08:47:55 PM PST
	> Modify Time: Sun 7 Aug 2021 22:50:00 PM PST
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
#include <json/json.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <string>
#include "logger.h"

int main() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd){
		LOG_FUNC_MSG("socket()", errnoMap[errno]);
		exit(0);
	}

	struct sockaddr_in ser = { { 0 } };
	ser.sin_family = AF_INET;

	std::string ip = "";
	std::cout << "please input information collector server ip address:";
	std::cin >> ip;

	unsigned short port = -1;
	std::cout << "please input information collector server port:";
	std::cin >> port;
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = inet_addr(ip.c_str());

	if(-1 == connect(sockfd,(struct sockaddr*)&ser, sizeof(ser))){
		LOG_FUNC_MSG("connect()", errnoMap[errno]);
		exit(0);
	}

	std::string id_card = "";
	std::cout << "please input the tourist's id_card:";
	std::cin >> id_card;
	std::string name = "";
	std::cout << "please input the tourist's name:";
	std::cin >> name;
	Json::Value value;
	value["name"] = name;
	value["id_card"] = id_card;
	send(sockfd, value.toStyledString().c_str(), strlen(value.toStyledString().c_str()), 0);

	char buf[BUF_LEN] = {0};
	
	recv(sockfd, buf, BUF_LEN-1, 0);
	std::cout << buf << std::endl;
	
	return 0;
}