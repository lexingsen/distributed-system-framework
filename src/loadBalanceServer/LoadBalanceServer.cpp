#include "LoadBalanceServer.h"
#include "logger.h"


event_base* LoadBalanceServer::m_base = nullptr;
ConsistentHashCircle* LoadBalanceServer::m_consistentHashCircle = nullptr;
TcpServer* LoadBalanceServer::m_server = nullptr;
TcpServer* LoadBalanceServer::m_client = nullptr;
std::map<int, PhysicalNode*>* LoadBalanceServer::m_physicalNodeMap = nullptr;
std::map<int, struct event*>* LoadBalanceServer::m_eventMap = nullptr;


LoadBalanceServer::LoadBalanceServer() {
    HashFunction* fun = new MD5HashFunction();
    m_consistentHashCircle = new ConsistentHashCircle(fun);
    m_base = event_base_new();
    m_physicalNodeMap = new std::map<int, PhysicalNode*>();
    m_eventMap = new std::map<int, struct event*>();

    string ipForClinet = "127.0.0.1";
    unsigned short portForClient = 6300;
    m_client = new TcpServer(ipForClinet, portForClient);

    string ipForServer = "127.0.0.1";
    unsigned short portForServer = 6200;
    m_server = new TcpServer(ipForServer, portForServer);

    std::cout << "wait for client and server to connect" << std::endl;
    struct event* listenServerEvent = event_new(m_base, m_server->getListenFd(), EV_READ|EV_PERSIST, LoadBalanceServer::listenServerCallBack, m_server);
    if (!listenServerEvent) {
        LOG_FUNC_MSG("event_new()", errnoMap[errno]);
        return ;
    }

    struct event* listenClientEvent = event_new(m_base, m_client->getListenFd(), EV_READ|EV_PERSIST, LoadBalanceServer::listenClientCallBack, m_client);
    if (!listenClientEvent) {
        LOG_FUNC_MSG("event_new()", errnoMap[errno]);
        return ;
    }

    event_add(listenServerEvent, nullptr);
    event_add(listenClientEvent, nullptr);
    event_base_dispatch(m_base);
}


void LoadBalanceServer::listenClientCallBack(int fd, short event, void* arg) {
    TcpServer* client = static_cast<TcpServer*>(arg);
    int cfd = client->Accept();
    if (-1 == cfd) {
        return;
    }
    struct sockaddr_in cli;
    socklen_t len = sizeof(cli);
    if (!getpeername(cfd, (struct sockaddr*)&cli, &len)) {
        std::cout << "client ip:" << inet_ntoa(cli.sin_addr) << std::endl;
        std::cout << "client port:" << ntohs(cli.sin_port) << std::endl;
    }
    std::string sock = inet_ntoa(cli.sin_addr) + to_string(ntohs(cli.sin_port));
    PhysicalNode* res = m_consistentHashCircle->searchPhysicalNode(sock);
    std::cout << "get physical node ip and port:" << res->getIp() << " ," << res->getPort() << std::endl;

    Json::Value val;
    val["ip"] = res->getIp();
    val["port"] = res->getPort();
    client->Send(cfd, val.toStyledString());
}


void LoadBalanceServer::listenServerCallBack(int fd, short event, void *arg) {
    TcpServer* server = static_cast<TcpServer*>(arg);
    int cfd = server->Accept();
    if (-1 == cfd) {
        return;
    }
    struct event* serverIOEvent = event_new(m_base, cfd, EV_READ|EV_PERSIST, LoadBalanceServer::ioEventCallBack, server);
    if (!serverIOEvent) {
        LOG_FUNC_MSG("event_new()", errnoMap[errno]);
        return;
    }
    m_eventMap->insert(make_pair(cfd, serverIOEvent));
    event_add(serverIOEvent, nullptr);
}

void LoadBalanceServer::ioEventCallBack(int fd, short event, void *arg) {
    TcpServer* server = static_cast<TcpServer*>(arg);
    std::string msg;
    if (server->Recv(fd, msg) <= 0) {
        std::cout << "server disconnected!" << std::endl;
        auto x = m_eventMap->find(fd);
        if (x != m_eventMap->end()) {
            event_free(x->second);
            m_eventMap->erase(fd);
        }
        auto y = m_physicalNodeMap->find(fd);
        if (y != m_physicalNodeMap->end()) {
            PhysicalNode* node = y->second;
            m_consistentHashCircle->removeVirtualNode(node);
            std::cout << "remove physical node, ip:" << node->getIp() << ", port:" << node->getPort() << std::endl;
            delete node;
            node = nullptr;
            m_physicalNodeMap->erase(fd);
        }
        std::cout << "========== physical node list ==========" << std::endl;
        auto z = m_physicalNodeMap->begin();
        if (z == m_physicalNodeMap->end()) {
            std::cout << "null" << std::endl;
        } else {
            for (; z != m_physicalNodeMap->end(); ++z) {
                std::cout << "fd:" << z->first << ",ip:" << z->second->getIp() << ", port:" << z->second->getPort() << std::endl;
            }
        }
        std::cout << "=======================================" << std::endl;
        close(fd);
    } else {
        Json::Value value;
        Json::Reader reader;
        if (!reader.parse(msg.c_str(), value)) {
            LOG_MSG("reader.parse error!");
            return;
        }
        std::cout << msg.c_str() << std::endl;
        std::string ip = value["ip"].toStyledString();
        ip = ip.substr(1, strlen(ip.c_str())-3);
        unsigned short port = value["port"].asInt();

        PhysicalNode* node = new PhysicalNode(10, ip, port);
        m_consistentHashCircle->addVirtualNode(node);
        m_physicalNodeMap->insert(make_pair(fd, node));
        
        std::cout << "============== physical node list ==============" << std::endl;
        for (auto it=m_physicalNodeMap->begin(); it!=m_physicalNodeMap->end(); ++it) {
            std::cout << it->first << ": ip:" << it->second->getIp() << ",port:" << it->second->getPort() << std::endl;
        }
        return;
    }
}