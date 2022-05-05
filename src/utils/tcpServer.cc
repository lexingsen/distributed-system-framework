#include "tcpServer.h"
#include "msg.h"
#include "logger.h"
#include "ipAddressPort.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#include <cstring>
#include <iostream>

// socket bind listen   fd->(ip+port)
TcpServer::TcpServer(const IpAddressPort& ipAddressAndPort) {
    m_lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == m_lfd) {
        LOG_FATAL << strerror(errno);
    }

    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    // 主机字节序 -》 网络字节序
    ser.sin_addr.s_addr = inet_addr(ipAddressAndPort.GetIpAddress().c_str());
    ser.sin_port = htons(ipAddressAndPort.GetPort());


    if (-1 == bind(m_lfd, (struct sockaddr*)&ser, sizeof(ser))) {
        LOG_FATAL << strerror(errno);
    }

    if (-1 == listen(m_lfd, 5)) {
        LOG_FATAL << strerror(errno);
    }
}

// close
TcpServer::~TcpServer() {
    if (-1 == close(m_lfd)) {
        LOG_FATAL << strerror(errno);
    }
}


// 从全连接队列中获取一个完成三次握手的cfd
int TcpServer::Accept() {
    struct sockaddr_in cli;
    socklen_t len = sizeof(cli);
    int cfd = accept(m_lfd, (struct sockaddr*)& cli, &len);
    if (-1 == cfd) {
        LOG_ERROR << strerror(errno);
        return -1;
    } else {
        char clientIpBuf[SMALL_BUF_LEN] = {0};
        if (!inet_ntop(AF_INET, &cli.sin_addr, clientIpBuf, SMALL_BUF_LEN))  {
            LOG_ERROR << strerror(errno);
        } else {
            // 数据的转换   网络字节序 -》 本机字节序
            std::string clientIp(clientIpBuf);
            unsigned short clientPort = ntohs(cli.sin_port);
            IpAddressPort ipAddressPort(clientIp, clientPort);
            LOG_INFO << ipAddressPort.ToString(); 
        }
    }
    return cfd;
}

int TcpServer::SendMsg(int cfd, const std::string& msg) {
    int numberOfSendByte = send(cfd, msg.c_str(), strlen(msg.c_str()), 0);
    if (-1 == numberOfSendByte) {
        LOG_ERROR << strerror(errno);
    }
    return numberOfSendByte;
}

Msg TcpServer::RecvMsg(int cfd) {
    char buf[LARGE_BUF_LEN] = {0};
    int numberOfRecvByte = recv(cfd, buf, LARGE_BUF_LEN, 0);
    if (-1 == numberOfRecvByte) {
        LOG_ERROR << strerror(errno);
    }
    return Msg{buf, numberOfRecvByte};
}

int TcpServer::GetLfd() const {
    return m_lfd;
}
