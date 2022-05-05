#include "thread.h"
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include "reactor.h"
#include "controller.h"

/* 
内存池 stl sgi 二级空间配置器   nginx
线程池
进程池
对象池
连接池
都是为了资源的服用
*/
Thread::Thread() {
    if (pthread_create(&m_tid, NULL, taskFunc, this)) {
        LOG_ERROR << "creat thread failed!";
    }
    // pipe(int* fd)
    if (-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, m_channel)) {
        LOG_ERROR << strerror(errno);
    }
}


Thread::~Thread() {
    pthread_join(m_tid, NULL);
}


int Thread::GetSocketPairFirst() const {
    return m_channel[0];
}

int Thread::GetSocketPairSecond() const {
    return m_channel[1];
}

pthread_t Thread::GetTid() const {
    return m_tid;
}

// one loop per thread reactor是抽象的 muduo libevent对reactor的一种实现 是具体的
// java netty
void* Thread::taskFunc(void* arg) {
    Thread* thread = static_cast<Thread*>(arg);
    thread->m_reactor = new Reactor();
    thread->m_ctroller = new Controller();
    thread->m_reactor->AddEventAndHander(thread->GetSocketPairSecond(), EV_READ | EV_PERSIST, Thread::SocketPairEventCallBack, arg);
    LOG_INFO << thread->GetTid();
    thread->m_reactor->Loop();
    return NULL;
}   

void Thread::SocketPairEventCallBack(int fd, short events, void* arg) {
    Thread* thread = static_cast<Thread*>(arg);
    int cfd = 0;
    if (read(fd, &cfd, 4) <= 0) {
        LOG_ERROR << strerror(errno);
    }
    // client io事件
    thread->m_reactor->AddEventAndHander(cfd, EV_READ | EV_PERSIST, Thread::ClientIOEventCallBack, arg);
}


void Thread::ClientIOEventCallBack(int fd, short events, void* arg) {
    Thread* thread = static_cast<Thread*>(arg);
    char buf[LARGE_BUF_LEN] = {0}; // wx 
    if (read(fd, buf, LARGE_BUF_LEN) <= 0) {
        LOG_INFO << "client disconneted!";
    }
    //
    LOG_INFO << buf;

    std::string data = buf;
    thread->m_ctroller->process(fd, data);
    // decode + compute + encode
    // mvc + myql + redis
}


// int main() {
//     Thread t;

//     sleep(1);
//     return 0;
// }