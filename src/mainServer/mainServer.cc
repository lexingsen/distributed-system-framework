#include "mainServer.h"
#include "tcpServer.h"
#include "reactor.h"
#include "threadPool.h"
#include "logger.h"
#include "ipAddressPort.h"
#include "mysqldb.h"
#include "redis.h"
#include <unistd.h>


MainServer::MainServer() {
    m_server = new TcpServer(IpAddressPort("127.0.0.1", 8300));
    m_pool = new ThreadPool(3);
    m_reactor = new Reactor();
    MySQLDB::GetInstance()->Connect(MYSQL_IP, lsc::MYSQLDB_PORT, USER, PASSWORD, DB);
    Redis::GetInstance()->Connect(REDIS_IP, REDIS_PORT);
    m_reactor->AddEventAndHander(m_server->GetLfd(), EV_READ | EV_PERSIST, MainServer::ListenEventCallBack, this);
    m_reactor->Loop();
}
MainServer::~MainServer() {}

void MainServer::ListenEventCallBack(int fd, short events, void* arg) {
    MainServer* mainServer = static_cast<MainServer*>(arg);
    if (EV_READ | events) {
        int cfd = mainServer->m_server->Accept();
        if (-1 == cfd) {
            LOG_ERROR << "Accept() failed!";
        }
        write(mainServer->m_pool->GetSubThreadSocketPairFirst(), (char*)&cfd, 4);
    }
}


int main() {
    MainServer ser;
    return 0;
}