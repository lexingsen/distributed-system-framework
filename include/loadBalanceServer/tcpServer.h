#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <string>
using namespace std;

class TcpServer {
public:
  TcpServer(const std::string& ip, unsigned short port);
  int Accept();
  int Send(int fd, const std::string& msg);
  int Recv(int fd, std::string& msg);
  int getListenFd() const;
  std::string getIp() const;
  unsigned short getPort() const;
private:  
  int m_listenFd;
  unsigned short m_port;
  std::string m_ip;
};


#endif
