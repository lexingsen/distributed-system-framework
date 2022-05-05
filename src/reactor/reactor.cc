#include "reactor.h"
#include "logger.h"


Reactor::Reactor() {
    m_reactor = event_base_new();
    if (!m_reactor) {
        LOG_ERROR << "event_base_new() failed!";
    }
}


Reactor::~Reactor() {}
void Reactor::AddEventAndHander(int fd, short events, event_callback_fn callback, void* arg) {
    struct event* ev = event_new(m_reactor, fd, events, callback, arg);
    if (!ev) {
        LOG_ERROR << "event_new() failed!";
    }
    if (-1 == event_add(ev, NULL)) {
        LOG_ERROR << "event_add() failed!";
    }

    
}
void Reactor::Loop() {
    event_base_dispatch(m_reactor);
}

// int main() {
//     return 0;
// }