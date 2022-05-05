#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>
#include <iostream>
#include "message.h"
#include "public.h"

// 单例模式 
/*
懒汉式
饿汉式
线程安全的单例模式

1、把构造函数私有化
2、提供生成对象的静态方法

单例模式  迭代器模式 简单工厂 抽象工厂 工厂方法  观察者模式 装饰器模式
*/


class Logger {
private:
    Logger();

    bool m_logToTerminal;
    bool m_logToLogFile;
    std::fstream m_logFile;
    LOG_LEVEL m_level;
public:
    static Logger* GetInstance() {
        static Logger logger;
        return &logger;
    }

    void SetLogToTerminal(bool logToTerminal);
    bool GetLogToTerminal() const;

    void SetLogToLogFile(bool logToLogFile);
    bool GetLogToLogFile() const;

    void SetLogFile(const std::string& logFileName = "dsf.log");

    void SetLogLevel(LOG_LEVEL level);
    LOG_LEVEL GetLogLevel() const;
    

    // 如何使用message类  类和类之间的关系 Logger&Message
    // void append(const Message& msg)
    void operator+=(const Message& msg) {
        if (m_logToTerminal) {
            // 打印到终端里边的日志 需要带颜色
            std::cout << msg.ToString(true) << std::endl;
        }

        if (m_logToLogFile) {
            m_logFile << msg.ToString(false) << std::endl;
        }

        if (msg.ToString().find("FATAL") != std::string::npos) {
            std::cout << "fatal happened!" << std::endl;
            exit(-1);
        }
    }
};

#endif


#define LOG(level) \
    if (level >= Logger::GetInstance()->GetLogLevel()) \
        *Logger::GetInstance() += Message(level, __FILE__, __FUNCTION__, __LINE__)

#define LOG_INFO  LOG(INFO)
#define LOG_ERROR LOG(ERROR)
#define LOG_DEBUG LOG(DEBUG)
// fatal exit(-1);
#define LOG_FATAL LOG(FATAL)

