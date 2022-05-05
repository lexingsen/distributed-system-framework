#ifndef __MAIN_SERVER_H__
#define __MAIN_SERVER_H__

class TcpServer;
class ThreadPool;
class Reactor;

class MainServer {
private:
    TcpServer* m_server;
    ThreadPool* m_pool;
    Reactor* m_reactor;
public:
    MainServer();
    ~MainServer();

    static void ListenEventCallBack(int fd, short events, void* arg);
};


#endif