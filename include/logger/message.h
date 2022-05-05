#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "public.h"
#include <sstream>
#include <string>


class Message {
private:
    std::string m_coloredHeader; // 打印到终端里
    std::string m_commonHeader;  // 打印到日志里
    std::string m_msg; // 日志信息

    // 格式化颜色
    std::string formatFieldWithColor(COLOR_NUMBER colorNumber, bool dark, 
    const std::string& delimiter, const std::string& fieldName, bool colored = true);
public:
    Message(LOG_LEVEL level, const std::string& fileName, 
    const std::string& functionName, int lineNumber);
    // [时间戳];[日志级别];[文件名称];[函数名称];[行号]
    std::string FormatHeader(LOG_LEVEL level, const std::string& fileName, 
    const std::string& functionName, int lineNumber, bool colored = true);
    std::string ToString(bool colored = true) const;

    template <typename T>  // helloworld
    Message& operator<<(const T& t) {
        std::stringstream ss;
        ss << t; // elloworld
        m_msg += ss.str();
        return *this;
    }
};


#endif
