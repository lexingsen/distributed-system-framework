#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <string>
using namespace std;

class TcpServer {
public:
  TcpServer(const string& ip, unsigned short port);
  int Accept();
  int Send(int fd, const string& msg);
  int Recv(int fd, string& msg);
  int getLinsenFd();
  string getIp();
  unsigned short getPort();
private:  
  int m_listenFd;
  unsigned short m_port;
  string m_ip;
};


#endif
