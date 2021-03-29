#include "tcpClient.h"
#include "logger.h"
#include "logger.h"

TcpClient::TcpClient() {}

TcpClient::~TcpClient() {
  close(m_fd);
}

int TcpClient::Connect(const std::string& ip, unsigned short port) {
  m_port = port;
  m_ip = ip;
  m_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == m_fd) {
    LOG_FUNC_MSG("socket()", errnoMap[errno]);
    return -1;
  }

  struct sockaddr_in ser;
  ser.sin_family = AF_INET;
  ser.sin_port = htons(m_port);
  ser.sin_addr.s_addr = inet_addr(m_ip.c_str());

  if (-1 == connect(m_fd, (struct sockaddr*)&ser, sizeof(ser))) {
    LOG_FUNC_MSG("connect()", errnoMap[errno]);
    return -1;
  }
  return m_fd;
}

int TcpClient::getFd() const {
  return m_fd;
}

std::string TcpClient::getIp() const {
  return m_ip;
}

unsigned short TcpClient::getPort() const {
  return m_port;
}

int TcpClient::Send(const std::string& msg) {
  return send(m_fd, msg.c_str(), strlen(msg.c_str()), 0);
}

int TcpClient::Recv(std::string& msg) {
  char buffer[1024] = {0};
  int n = recv(m_fd, buffer, 1023, 0);
  msg = buffer;
  return n;
}