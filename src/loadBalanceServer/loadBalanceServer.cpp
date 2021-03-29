#include "loadBalanceServer.h"
#include "logger.h"
#include "logger.h"
#include <unistd.h>

PhysicalNode::PhysicalNode():m_cnt(0) {}
PhysicalNode::PhysicalNode(int cnt, const string& ip, unsigned short port):
  m_cnt(cnt),m_ip(ip), m_port(port) {
  
}

void PhysicalNode::setPhysicalNode(const string& ip, unsigned short port) {
  this->m_ip = ip;
  this->m_port = port;
}

int PhysicalNode::getVirtualNodeCnt() {
  return m_cnt;
}

unsigned short PhysicalNode::getPort() {
  return m_port;
}

string PhysicalNode::getIp() {
  return m_ip;
}


VirtualNode::VirtualNode() {

}

VirtualNode::VirtualNode(PhysicalNode* father) {
  this->m_hashValue = -1;
  this->m_father = father;
}
void VirtualNode::setVirtualNode(PhysicalNode* father) {
  this->m_father = father;
}

PhysicalNode* VirtualNode::getFatherPhysicalNode() {
  return this->m_father;
}

void VirtualNode::setHash(long hash) {
  this->m_hashValue = hash;
}

long VirtualNode::getHash() {
  return this->m_hashValue;
}

long MD5HashFunction::getHashValue(const std::string& sock) {
  long hashValue = 0;
  unsigned char x[16];
  bzero(x, sizeof(x));
  MD5_CTX md5;
  MD5_Init(&md5);
  MD5_Update(&md5, sock.c_str(), strlen(sock.c_str()));
  MD5_Final(x, &md5);

  for (int i=0; i<4; ++i) {
    hashValue += ((long)(x[i*4+3]&0xff) << 24) |
    ((long)(x[i*4+2]&0xff) << 16) |
    ((long)(x[i*4+1]&0xff) << 8 ) |
    ((long)(x[i*4+0]&0xff) << 0 );
  }
  return hashValue;
}

ConsistentHashCircle::ConsistentHashCircle(HashFunction* fun) {
  if (!fun) {
    LOG_FUNC_ERROR("parameter fun is nullptr");
    return;
  }
  this->m_fun = fun;
  this->m_virtualNodeCnt = 0;
  this->m_virtualNodeMap = new map<unsigned long, VirtualNode*>();
}


ConsistentHashCircle::~ConsistentHashCircle() {

}

void ConsistentHashCircle::setHashFunction(HashFunction* fun) {
  this->m_fun = fun;
}

int ConsistentHashCircle::addVirtualNode(PhysicalNode* node) {
  if (!node) {
    LOG_MSG("the physical node is null!");
    return -1;
  }
  if (node->getVirtualNodeCnt() <= 0) {
    LOG_MSG("the physical node has not virtual node!");
    return -1;
  }
  string sock = node->getIp() + to_string(node->getPort());

  string tmp = sock;
  VirtualNode* virtualNode;
  unsigned long hash;
  for (int i=0; i<node->getVirtualNodeCnt(); ++i) {
    virtualNode = new VirtualNode(node);
    tmp += to_string(i);
    hash = this->m_fun->getHashValue(tmp);
    auto it = m_virtualNodeMap->find(hash);
    if (it == m_virtualNodeMap->end()) {
      if (virtualNode) {
        m_virtualNodeMap->insert(make_pair(hash, virtualNode));
        this->m_virtualNodeCnt ++;
      }
    } else {
      LOG_MSG("find hash conflict!");
      return -1;
    }
    tmp = sock;
  }

  auto it = m_virtualNodeMap->begin();
  if (it == m_virtualNodeMap->end()) {
    cout << "there has no virtual node!"  << endl;
  } else {
    cout << "============ virtual node list ============" << endl;
    for (auto x=m_virtualNodeMap->begin(); x!=m_virtualNodeMap->end(); ++x) {
      cout << x->first << ":" << " ip:" << x->second->getFatherPhysicalNode()->getIp() << " port:" << x->second->getFatherPhysicalNode()->getPort() << endl;
    }
    cout << "===========================================" << endl;
  }

  cout << "success addPhysicalNode's virtual node!" << endl;
  return 0;
}

int ConsistentHashCircle::removeVirtualNode(PhysicalNode* node) {
  if (!node) return -1;
  string sock = node->getIp() + to_string(node->getPort());

  string tmp = sock;
  unsigned long hash = 0;
  for (int i=0; i<node->getVirtualNodeCnt(); ++i) {
    tmp += to_string(i);
    hash = m_fun->getHashValue(tmp);
    m_virtualNodeMap->erase(hash);
    m_virtualNodeCnt --;
    tmp = sock;
  }

  auto it = m_virtualNodeMap->begin();
  if (it == m_virtualNodeMap->end()) {
    cout << "there has no virtual node!"  << endl;
  } else {
    cout << "============ virtual node list ============" << endl;
    for (auto x=m_virtualNodeMap->begin(); x!=m_virtualNodeMap->end(); ++x) {
      cout << x->first << ":" << " ip:" << x->second->getFatherPhysicalNode()->getIp() << " port:" << x->second->getFatherPhysicalNode()->getPort() << endl;
    }
    cout << "===========================================" << endl;
  }
  cout << "success remove physicalNode's virtual node!" << endl;
  return 0;
}


PhysicalNode* ConsistentHashCircle::searchPhysicalNode(const string& sock) {
  unsigned long hash = this->m_fun->getHashValue(sock);
  auto it = m_virtualNodeMap->lower_bound(hash);
  if (it == m_virtualNodeMap->end()) {
    it = m_virtualNodeMap->begin();
  }
  VirtualNode* res = it->second;
  if (!res) return nullptr;
  else return res->getFatherPhysicalNode();
}

int ConsistentHashCircle::getVirtualNodeCnt() {
  return m_virtualNodeCnt;
}

event_base* LoadBalanceServer::m_base = nullptr;
ConsistentHashCircle* LoadBalanceServer::m_consistentHashCircle = nullptr;
TcpServer* LoadBalanceServer::m_server = nullptr;
TcpServer* LoadBalanceServer::m_client = nullptr;
map<int, PhysicalNode*>* LoadBalanceServer::m_physicalNodeMap = nullptr;
map<int, struct event*>* LoadBalanceServer::m_eventMap = nullptr;


LoadBalanceServer::LoadBalanceServer() {
  HashFunction* fun = new MD5HashFunction();
  m_consistentHashCircle = new ConsistentHashCircle(fun);
  m_base = event_base_new();
  m_physicalNodeMap = new map<int, PhysicalNode*>();
  m_eventMap = new map<int, struct event*>();

  string ipForClinet = "127.0.0.1";
  unsigned short portForClient = 6300;
  #if 0
  cout << "please input the ip for client to connect:";
  cin >> ipForClinet;
  cout << "please input the port for client to connect:";
  cin >> portForClient;
  #endif
  m_client = new TcpServer(ipForClinet, portForClient);

  string ipForServer = "127.0.0.1";
  unsigned short portForServer = 6200;
  #if 0
  cout << "please input the ip for server to connect:";
  cin >> ipForServer;
  cout << "please input the port for server to connect:";
  cin >> portForServer;
  #endif
  m_server = new TcpServer(ipForServer, portForServer);


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
  if (-1 == cfd) return;
  struct sockaddr_in cli;
  socklen_t len = sizeof(cli);
  if (!getpeername(cfd, (struct sockaddr*)&cli, &len)) {
    cout << "client ip:" << inet_ntoa(cli.sin_addr) << endl;
    cout << "client port:" << ntohs(cli.sin_port) << endl;
  }
  string sock = inet_ntoa(cli.sin_addr) + to_string(ntohs(cli.sin_port));
  PhysicalNode* res = m_consistentHashCircle->searchPhysicalNode(sock);
  cout << "get physical node ip and port:" << res->getIp() << " ," << res->getPort() << endl;

  Json::Value val;
  val["ip"] = res->getIp();
  val["port"] = res->getPort();
  client->Send(cfd, val.toStyledString());
}


void LoadBalanceServer::listenServerCallBack(int fd, short event, void *arg) {
  TcpServer* server = static_cast<TcpServer*>(arg);
  int cfd = server->Accept();
  if (-1 == cfd) return;
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
  string msg;
  if (server->Recv(fd, msg) <= 0) {
    cout << "server disconnected!" << endl;
    auto x = m_eventMap->find(fd);
    if (x != m_eventMap->end()) {
      event_free(x->second);
      m_eventMap->erase(fd);
    }
    auto y = m_physicalNodeMap->find(fd);
    if (y != m_physicalNodeMap->end()) {
      PhysicalNode* node = y->second;
      m_consistentHashCircle->removeVirtualNode(node);
      cout << "remove physical node, ip:" << node->getIp() << ", port:" << node->getPort() << endl;
      delete node;
      node = nullptr;
      m_physicalNodeMap->erase(fd);
    }
    cout << "========== physical node list ==========" << endl;
    auto z = m_physicalNodeMap->begin();
    if (z == m_physicalNodeMap->end()) {
      cout << "null" << endl;
    } else {
      for (; z != m_physicalNodeMap->end(); ++z) {
        cout << "fd:" << z->first << ",ip:" << z->second->getIp() << ", port:" << z->second->getPort() << endl;
      }
    }
    cout << "=======================================" << endl;
    close(fd);
  } else {
    Json::Value value;
    Json::Reader reader;
    if (!reader.parse(msg.c_str(), value)) {
      LOG_MSG("reader.parse error!");
      return;
    }
    cout << msg.c_str() << endl;
    string ip = value["ip"].toStyledString();
    ip = ip.substr(1, strlen(ip.c_str())-3);
    unsigned short port = value["port"].asInt();

    PhysicalNode* node = new PhysicalNode(10, ip, port);
    m_consistentHashCircle->addVirtualNode(node);
    m_physicalNodeMap->insert(make_pair(fd, node));
    
    cout << "============== physical node list ==============" << endl;
    for (auto it=m_physicalNodeMap->begin(); it!=m_physicalNodeMap->end(); ++it) {
      cout << it->first << ": ip:" << it->second->getIp() << ",port:" << it->second->getPort() << endl;
    }
    return;
  }
}