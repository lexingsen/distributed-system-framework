#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


class TcpClient {
private:
  std::string m_ip;  
  unsigned short m_port;
  int m_fd;
public:
  int getFd();
  unsigned short getPort();
  std::string getIp();

  TcpClient();
  ~TcpClient();
  int Connect(const std::string& ip, unsigned short port);
  int Send(const std::string& msg);
  int Recv(std::string& msg);
};



#endif 