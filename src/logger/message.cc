#include "message.h"
#include "timeStamp.h"

#include <iostream>


// 格式化颜色  
std::string Message::formatFieldWithColor(COLOR_NUMBER colorNumber, bool dark, 
    const std::string& delimiter, const std::string& fieldName, bool colored) {
    std::stringstream ss; // ss << xx
    if (colored) {
        ss << "\033[" << dark << ";" << colorNumber << "m";
    }
    ss << fieldName;
    if (colored) {
        ss << "\033[0m"; // 重置属性
    }
    ss << delimiter;
    return ss.str();
}

Message::Message(LOG_LEVEL level, const std::string& absoluteFileName, 
    const std::string& functionName, int lineNumber) {
    std::string fileName = absoluteFileName;
    int pos = 0;
    for (int i = fileName.length() - 1; i >= 0; --i) {
        if (fileName[i] == '/') {
            pos = i;
            break;
        }
    }
    fileName = fileName.substr(pos + 1, fileName.length() - pos);
    m_coloredHeader = FormatHeader(level, fileName, functionName, lineNumber, true);
    m_commonHeader  = FormatHeader(level, fileName, functionName, lineNumber, false);
}
// [时间戳][日志级别][文件名称][函数名称][行号]
std::string Message::FormatHeader(LOG_LEVEL level, const std::string& fileName, 
    const std::string& functionName, int lineNumber, bool colored) {
    // 时间戳
    std::stringstream ss;
    ss << formatFieldWithColor(DEFAULT_COLOR, 0, "", TimeStamp::Now().ToString(), colored);

    // 日志级别  INFO -> "[INFO]"
    COLOR_NUMBER logColorNumber = LogLevelColor[level];
    std::string logLevelType = LogLevelTypeString[level];
    ss << formatFieldWithColor(logColorNumber, 1, "", logLevelType, colored);
    
    // 文件名称
    COLOR_NUMBER fileColor = LogFeildColor[FILE_NAME];
    ss << formatFieldWithColor(fileColor, 1, "", "[" + fileName + "]", colored);

    // 函数名称
    COLOR_NUMBER functionColor = LogFeildColor[FUNCTION_NAME];
    ss << formatFieldWithColor(functionColor, 1, "",  "[" + functionName + "]", colored);

    // 行号
    COLOR_NUMBER lineColor = LogFeildColor[LINE_NUMBER];
    ss << formatFieldWithColor(lineColor, 1, " : ",  "[" + std::to_string(lineNumber) + "]", colored);

    return ss.str();
}

std::string Message::ToString(bool colored) const {
    return colored ? m_coloredHeader + m_msg : m_commonHeader + m_msg;
}
