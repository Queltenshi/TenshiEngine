#pragma once

#include <string>
#include <iostream>

namespace te{

enum class LogLevel{DEBUG, INFO, WARNING, ERROR, CRITICAL};

class Logger{

public:
    Logger()=delete;
    Logger(const Logger&)=delete;
    Logger(Logger&&)=delete; 

    inline static LogLevel currentLevel = LogLevel::DEBUG;

    static void debug(const std::string &source, const std::string &message);
    static void warning(const std::string &source, const std::string &message);
    static void error(const std::string &source, const std::string &message);
    static void info(const std::string &source, const std::string &message);
    static void critical(const std::string &source, const std::string &message);

private:
    static void log(LogLevel logLevel, const std::string &system, const std::string &message);
    static std::string toString(LogLevel logLevel) {
        switch (logLevel) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARNING:  return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::CRITICAL: return "CRITICAL";
        }
        return "UNKNOWN";
    }
};

}

/**
 * @brief Logs a debug message
 *
 * Logs a debug message if the currentLevel is set to DEBUG
 * @param source The source or module where the log originates
 * @param message The message to log
 *
 * @macro LOG_DEBUG
 */
#define LOG_DEBUG(source, message) \
    do { \
        if (te::Logger::currentLevel == te::LogLevel::DEBUG) { \
            te::Logger::debug(source, message); \
        } \
    } while(0)
