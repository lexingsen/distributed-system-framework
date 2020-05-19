#include "thread.h"


void clientIOEventCallBack(int fd, short event, void *arg) {
  Thread* thread = static_cast<Thread*>(arg);
  char buffer[1024] = {0};
  if (recv(fd, buffer, 1023, 0) <= 0) {
    std::cout << "client disconnected!" << std::endl;
    close(fd);
    return;
  } 
  std::cout << "============ client data ============" << endl;
  string msg(buffer);
  Json::Value value;
  Json::Reader reader;

  if (!reader.parse(msg, value)) {
    LOG("convert json object error!");
    return;
  }
  thread->m_controller->process(fd, value);
}

void socketPairIOEventCallBack(int fd, short event, void *arg) {
  Thread* thread = static_cast<Thread*>(arg);
  int cfd = 0;
  if (recv(fd, &cfd, 4, 0) <= 0) {
    LOG("recv error!");
    return ;
  }
  struct event* clientIOEvent = event_new(thread->m_base, cfd, EV_READ|EV_PERSIST, clientIOEventCallBack, thread);
  if (!clientIOEvent) {
    LOG("event new error!");
    return;
  }
  event_add(clientIOEvent, nullptr);
  thread->m_eventMap->insert(make_pair(cfd, clientIOEvent));
}


void* threadTaskFunction(void *arg) {
  Thread* thread = static_cast<Thread*>(arg);
  thread->m_base = event_init();
  struct event* socketPairIOEvevnt = event_new(thread->m_base, thread->m_socketpairFd[1], EV_PERSIST|EV_READ, socketPairIOEventCallBack, thread);
  if (!socketPairIOEvevnt) {
    LOG("event_new socketPairEvent error");
    exit(0);
  }
  event_add(socketPairIOEvevnt, nullptr);
  event_base_dispatch(thread->m_base);
}

Thread::Thread() {
  m_controller = new Controller();
  if (-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, m_socketpairFd)) {
    LOG("socketpait error!");
    return ;
  }
  int res = pthread_create(&m_id, nullptr, threadTaskFunction, this);
  if (res != 0) {
    LOG("pthread_create error");
    return ;
  }
}

Thread::~Thread() {
  event_base_free(m_base);
  delete m_controller;
}


int Thread::getEventMapSize() {
  return m_eventMap->size();
}

int Thread::getSocketPairFdFirst() {
  return m_socketpairFd[0];
}

int Thread::getSocketPairFdSecond() {
  return m_socketpairFd[1];
}

pthread_t Thread::getId() {
  return m_id;
}
