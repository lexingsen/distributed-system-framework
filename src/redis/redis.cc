#include "redis.h"
#include "logger.h"
#include "public.h"
#include <sstream>
#include <string.h>


Redis::Redis() {}
bool Redis::Connect(const std::string& ip, unsigned short port) {
    m_redisContext = redisConnect(ip.c_str(), port);
    if (m_redisContext && m_redisContext->err) {
        LOG_ERROR << "redis connect exception:" << m_redisContext->errstr;
        return false;
    }
    LOG_INFO << "redis connect success!";
    return true;
}

Redis::~Redis() {
    redisFree(m_redisContext);
}
bool Redis::Set(const std::string& key, const std::string& val) {
    std::stringstream ss;
    ss << "set " << key << " " << val;
    redisReply* res = (redisReply*)redisCommand(m_redisContext, ss.str().c_str());
    if (!res) {
        LOG_ERROR << "set key failed!";
        return false;
    }

    if (!(res->type == REDIS_REPLY_STATUS) && strcasecmp(res->str, "ok") == 0) {
        LOG_ERROR << "failed to execute command";
        freeReplyObject(res);
        return false;
    }

    freeReplyObject(res);
    return true;
}

std::string Redis::Get(const std::string& key) {
    std::stringstream ss;
    ss << "get " << key;
    redisReply* res = (redisReply*)redisCommand(m_redisContext, ss.str().c_str());
    if (!res) {
        LOG_ERROR << "set key failed!";
        return "";
    }

    if (res->type != REDIS_REPLY_STRING) {
        LOG_ERROR << "failed to execute command";
        freeReplyObject(res);
        return "";
    }
    std::string result = res->str;
    freeReplyObject(res);
    return result;
}

// int main() {
//     Redis::GetInstance()->Connect(REDIS_IP, REDIS_PORT);
//     Redis::GetInstance()->Set("hello", "world");
//     std::cout << Redis::GetInstance()->Get("hello") << std::endl;
//     return 0;
// }