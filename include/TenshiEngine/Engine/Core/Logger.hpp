#pragma once

#include <string>
#include <iostream>

namespace te{

enum class LogLevel{DEBUG, INFO, WARNING, ERROR};

class Logger{

public:
    Logger()=delete;
    Logger(const Logger&)=delete;
    Logger(Logger&&)=delete; 

    inline static LogLevel currentLevel = LogLevel::DEBUG;

    static void log(LogLevel logLevel, const std::string &system, const std::string &message);
    static void debug(const std::string &source, const std::string &message);

private:
    static std::string toString(LogLevel logLevel) {
        switch (logLevel) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARNING:  return "WARNING";
            case LogLevel::ERROR: return "ERROR";
        }
        return "UNKNOWN";
    }
};

#define LOG_DEBUG(source, message) \
    do { \
        if (Logger::currentLevel == LogLevel::DEBUG) { \
            Logger::debug(source, message); \
        } \
    } while(0)

}
