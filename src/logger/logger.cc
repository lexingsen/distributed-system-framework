#include "logger.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// 通过环境变量来设置日志级别的
// log.ini 配置文件
Logger::Logger() {
    // if (NULL == getenv("LOG_LEVEL"))
    // if (nullptr == getenv("LOG_LEVEL"))
    if (!getenv("LOG_LEVEL")) {
        m_level = INFO;
    } else {
        // for if 嵌套的层数 == 圈复杂度
        // 断言 getenv("LOG_LEVEL")的返回值一定是 "INFO" "ERROR" "DEBUG" "FATAL"
        m_level = LogLevelType[getenv("LOG_LEVEL")];
    }
    m_logToLogFile = true;
    m_logToTerminal = true;
}

void Logger::SetLogToTerminal(bool logToTerminal) {
    m_logToTerminal = logToTerminal;
}

bool Logger::GetLogToTerminal() const {
    return m_logToTerminal;
}

void Logger::SetLogToLogFile(bool logToLogFile) {
    m_logToLogFile = logToLogFile;
}

bool Logger::GetLogToLogFile() const {
    return m_logToLogFile;
}


void Logger::SetLogLevel(LOG_LEVEL level) {
    m_level = level;
}
LOG_LEVEL Logger::GetLogLevel() const {
    return m_level;
}

// dsf.log
void Logger::SetLogFile(const std::string& logFileName) {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
    m_logFile.open(logFileName);
    m_logToLogFile = true;
}