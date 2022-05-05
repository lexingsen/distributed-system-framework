#ifndef __REDIS_H__
#define __REDIS_H__

#include <string>
#include <hiredis/hiredis.h>



// 线程安全的单例类
class Redis {
private:
    redisContext* m_redisContext; // client
    Redis();
public:
    static Redis* GetInstance() {
        static Redis redis;
        return &redis;
    }
    bool Connect(const std::string&, unsigned short);
    ~Redis();
    bool Set(const std::string&, const std::string&);
    std::string Get(const std::string&);
};



#endif