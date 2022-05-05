// 自定义的
#include "tcpClient.h"
#include "logger.h"
#include "public.h"
#include "ipAddressPort.h"
#include "msg.h"

// linux api的
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// c标准库的
#include <cstring>  // #include <string.h>

TcpClient::TcpClient(const IpAddressPort& ipAddressAndPort) {
    // tcp 
    m_sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == m_sfd) {
        LOG_FATAL << strerror(errno);
    }

    struct sockaddr_in ser; 
    // 本机字节序 -》 网络字节序
    // intel 小端模式  -》 网络字节序 大端模式
    ser.sin_family = AF_INET;
    ser.sin_port = htons(ipAddressAndPort.GetPort());
    ser.sin_addr.s_addr = inet_addr(ipAddressAndPort.GetIpAddress().c_str());
    if (-1  == connect(m_sfd, (struct sockaddr*)&ser, sizeof(ser)))  {
        LOG_FATAL << strerror(errno);
    }
    LOG_INFO << "connect success!";
}

TcpClient::~TcpClient() {
    if (-1 == close(m_sfd))  {
        // log_fatal
        LOG_FATAL << strerror(errno);
    }
}

int TcpClient::SendMsg(const std::string& msg) {
    // send
    int numberOfSendByte = send(m_sfd, msg.c_str(), strlen(msg.c_str()), 0);
    if (-1 == numberOfSendByte) {
        LOG_ERROR << strerror(errno);
    }
    return numberOfSendByte;
}

// 本质问题？ 怎么返回多个返回值
Msg TcpClient::RecvMsg() {
    // recv api
    char buf[LARGE_BUF_LEN] = {0};
    int numberOfRecvByte = recv(m_sfd, buf, LARGE_BUF_LEN, 0);
    if (-1 == numberOfRecvByte) {
        LOG_ERROR << strerror(errno);
    }
    // c风格
    // return Msg{.m_msg = buf, .m_numberOfRecvBytes = numberOfRecvByte};
    return Msg{buf, numberOfRecvByte};
}

int TcpClient::GetSfd() const {
    return m_sfd;
}


int main() {
    IpAddressPort ser("127.0.0.1", 5000);
    TcpClient client(ser);
    client.SendMsg("hello world");
    return 0;
}
