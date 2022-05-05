#ifndef __PUBLIC_H__
#define __PUBLIC_H__
#include <map>
#include <unordered_map>

static const int SMALL_BUF_LEN = 128;
static const int MEDIAN_BUF_LEN = 512;
static const int LARGE_BUF_LEN = 1024;

enum COLOR_NUMBER {
    DEFAULT_COLOR = 0,
    INFO_COLOR  = 36,   
    ERROR_COLOR = 35,
    DEBUG_COLOR = 32,
    FATAL_COLOR = 31,
    LINE_COLOR = 32,
    FUNCTION_COLOR = 34,
    FILE_COLOR = 35,
};

enum LOG_LEVEL {
    INFO = 0,
    ERROR,
    DEBUG,
    FATAL
};


enum LOG_FEILD {
    LINE_NUMBER = 0,
    FUNCTION_NAME,
    FILE_NAME
};


// .data .text .bss

// unordered_map hash表 存取  查找时间复杂度O(1)
// 这张表表示的 日志级别到对应颜色的映射关系
static std::unordered_map<LOG_LEVEL, COLOR_NUMBER> LogLevelColor = {
    {INFO,  INFO_COLOR}, 
    {ERROR, ERROR_COLOR}, 
    {DEBUG, DEBUG_COLOR}, 
    {FATAL, FATAL_COLOR}
};

// 这张表表示的 字段(file function line)到对应颜色的映射关系
static std::unordered_map<LOG_FEILD, COLOR_NUMBER> LogFeildColor = {
    {LINE_NUMBER, LINE_COLOR}, 
    {FUNCTION_NAME, FUNCTION_COLOR}, 
    {FILE_NAME, FILE_COLOR}
};

// 这张表表示的 日志级别到对应字符串的映射关系
static std::unordered_map<LOG_LEVEL, std::string> LogLevelTypeString = {
    {INFO, "[INFO]"},
    {ERROR, "[ERROR]"},
    {DEBUG, "[DEBUG]"},
    {FATAL, "[FATAL]"}
};

static std::unordered_map<std::string, LOG_LEVEL> LogLevelType = {
    {"INFO", INFO},
    {"ERROR", ERROR},
    {"DEBUG", DEBUG},
    {"FATAL", FATAL}
};



enum BIZTYPE {
    LOGIN = 0,
    REGISTER = 1,   
};

static const std::string REDIS_IP = "127.0.0.1";
static const unsigned short REDIS_PORT = 6389;
static const std::string MYSQL_IP = "127.0.0.1";
namespace lsc{
    static const unsigned short MYSQLDB_PORT = 3306;
};
static const std::string USER = "root";
static const std::string PASSWORD = "1234"; 
static const std::string DB = "dsf";


#endif