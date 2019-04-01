/*************************************************************************
    > File Name: lb.h
    > Author: lisicheng
    > Mail: 1050592374@qq.com 
    > Created Time: Fri 11 Jan 2019 06:27:29 PM PST
 ************************************************************************/

#ifndef __LB_H__
#define __LB_H__
#include <iostream>
#include <string>
#include <map>
#include <event.h>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <pthread.h>
#include <openssl/md5.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>
#include "tcpServer.h"
using namespace std;


class Node{
private:
	int _vNodeNum;
	string _ip;
	short _port;
public:
	Node();
	Node(int count, const string& ip, short port);

	int getVNodeNum();
	void setNode(const string& ip, short port);
	string getIp();
	short getPort();
};


class VNode{
private:
	long _hash;
	Node* _node;//虚拟节点所指向的实体节点
public:
	VNode();
	VNode(Node* node);
	void setVNode(Node* node);
	
	Node* getPNode();
	void setHash(long hash);
	long getHash();
};

class HashFun{
public:
	virtual long getHashVal(const string& address) = 0;
};

class MD5HashFun:public HashFun{
public:
	virtual long getHashVal(const string& address);
};

//一致性hash
class ConHash{
public:
	ConHash(HashFun* pfun);
	void  setHashFun(HashFun* pfun);
	int   addNode(Node* node);
	int   delNode(Node* node);
	int   getVNode();
	Node* searchPNode(const string& pnode);
private:
	HashFun* _pfun;
	int _vNodeNum;
	map<unsigned long, VNode*>* _VNodeMap;
};

class LBserver{
public:
	LBserver();
	static void io_server(int fd, short event, void* arg);
	static void listenclient_cb(int fd, short event, void* arg);
	static void listenserver_cb(int fd, short event, void* arg);
private:
	static TcpServer* _lb_server;
	static TcpServer* _lb_client;

	static event_base* _base;
	static ConHash* _hash;
	
	static map<int, Node*>* _serverMap;
	static map<int, struct event*>* _eventMap;
};


#endif

