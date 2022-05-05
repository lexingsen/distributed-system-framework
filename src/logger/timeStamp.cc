#include "timeStamp.h"
#include "public.h"
#include "message.h"
#include <ctime>
#include <iostream>



// don't talk, show me code.
TimeStamp::TimeStamp() : m_secondSinceEpoch(0) {}
TimeStamp::TimeStamp(uint64_t secondSinceEpoch)
     : m_secondSinceEpoch(secondSinceEpoch) 
    {}

// secondSinceEpoch -> localtime -> struct tm  -> std::string
// sprintf snprintf
std::string TimeStamp::ToString() {
    struct tm t;
    localtime_r(&m_secondSinceEpoch, &t);

    // 2的幂次   魔鬼数字
    char buf[SMALL_BUF_LEN] = {0};
    snprintf(buf, SMALL_BUF_LEN, "[%04d/%02d/%02d %02d:%02d:%02d]", 
        t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    return buf;
}

// time
TimeStamp TimeStamp::Now() {
    return TimeStamp(time(NULL));
}
