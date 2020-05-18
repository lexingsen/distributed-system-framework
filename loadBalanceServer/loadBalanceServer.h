#include <iostream>
#include <string>
#include <map>
#include <event.h>
#include <string.h>
#include <openssl/md5.h>
#include <json/json.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "tcpServer.h"
using namespace std;

class PysicalNode {
private:  
  int m_cnt;
  string m_ip;
  unsigned short m_port;
public:
  PysicalNode();
  PysicalNode(int cnt, const string& io, unsigned short port);
  int getVirtualNodeCnt();
  void setPysicalNode(const string& ip, unsigned short port);
  string getIp();
  unsigned short getPort();
};

class VirtualNode {
private:
  long m_hashValue; // 虚拟节点对应的hash值
  PysicalNode* m_father;
public:
  VirtualNode();
  VirtualNode(PysicalNode* father);
  void setVirtualNode(PysicalNode* father);
  PysicalNode* getFatherPysiaclNode();
  void setHash(long hash);
  long getHash();
};


class HashFunction {
public:
  virtual long getHashValue(const string& sock) = 0;  
};

class MD5HashFunction : public HashFunction {
  virtual long getHashValue(const string& sock);
};


class ConsistentHashCircle{
public:
  ConsistentHashCircle(HashFunction* fun);
  ~ConsistentHashCircle();
  void setHashFunction(HashFunction* fun);
  int addVirtualNode(PysicalNode* node);
  int removeVirtualNode(PysicalNode* node);
  int getVirtualNodeCnt();
  PysicalNode* searchPysicalNode(const string& sock);
private:
  HashFunction* m_fun;
  int m_virtualNodeCnt;
  map<unsigned long, VirtualNode*>* m_virtualNodeMap;
};

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
  static map<int, PysicalNode*>* m_pysicalNodeMap;
  static map<int, struct event*>* m_eventMap;
};