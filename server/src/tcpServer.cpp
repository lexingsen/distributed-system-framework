#include "tcpServer.h"
#include "public.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>



TcpServer::TcpServer(const string& ip, unsigned short port) :
  m_ip(ip), m_port(port) {
    m_listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == m_listenFd) {
      LOG("socket create error!");
    }

    struct sockaddr_in ser;
    bzero(&ser, sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(m_port);
    ser.sin_addr.s_addr = inet_addr(m_ip.c_str());

    if (-1 == bind(m_listenFd, (struct sockaddr*)&ser, sizeof(ser))) {
      LOG("bind error!");
      return;
    }
    if (-1 == listen(m_listenFd, 5)) {
      LOG("listen error!");
      return;
    }
}

int TcpServer::Accept() {
  struct sockaddr_in cli;
  socklen_t len = sizeof(cli);
  int cfd = accept(m_listenFd, (struct sockaddr*)&cli, &len);
  if (-1 == cfd) {
    LOG("accpet error!");
    return -1;
  }
  return cfd;
}

int TcpServer::Send(int fd, const string& msg) {
  return send(fd, msg.c_str(), strlen(msg.c_str()), 0);
}

int TcpServer::Recv(int fd, string &msg) {
  char buffer[1024] = {0};
  int n = recv(fd, buffer, 1023, 0);
  msg = buffer;
  return n;
}

int TcpServer::getLinsenFd() {
  return m_listenFd;
}

unsigned short TcpServer::getPort() {
  return m_port;
}

string TcpServer::getIp() {
  return m_ip;
}