#pragma once

#include <event.h>
#include <string.h>

#include <json/json.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "TcpServer.h"
#include "PysicalNode.h"
#include "ConsistentHashCircle.h"



class LoadBalanceServer {
public:
    LoadBalanceServer();
    static void ioEventCallBack(int fd, short event, void* arg);
    static void listenClientCallBack(int fd, short event, void* arg);
    static void listenServerCallBack(int fd, short event, void* arg);
private:
    static TcpServer* m_server;
    static TcpServer* m_client;
    static event_base* m_base;
    static ConsistentHashCircle* m_consistentHashCircle;
    static std::map<int, PhysicalNode*>* m_physicalNodeMap;
    static std::map<int, struct event*>* m_eventMap;
};