#include "TenshiEngine/Engine/Core/Logger.hpp"
#include <string>

namespace te{

void Logger::log(LogLevel logLevel, const std::string &system, const std::string &message){
    std::cout << "[" + system + "] " + toString(logLevel) + ": " + message + "\033[0m"<< std::endl;;  
}

void Logger::debug(const std::string &source, const std::string &message){
    log(LogLevel::DEBUG, source, message);
}

void Logger::debug(const std::string &source, const std::string &componentName, const components::Component *component, const EntityID entityID){
    log(LogLevel::DEBUG, source, componentName  + " changed for Entity " + std::to_string(entityID) + " " + component->toString());
}

void Logger::info(const std::string &source, const std::string &message){
    log(LogLevel::INFO, source, message);
}

void Logger::warning(const std::string &source, const std::string &message){
    log(LogLevel::WARNING, source, message);
}

void Logger::error(const std::string &source, const std::string &message){
    log(LogLevel::ERROR, source, message);
}

void Logger::critical(const std::string &source, const std::string &message){
    log(LogLevel::FATAL, source, message);
}

std::string Logger::toString(LogLevel logLevel) {
    switch (logLevel) {
        case LogLevel::DEBUG: return "\033[34mDEBUG";
        case LogLevel::INFO:  return "\033[32mINFO";
        case LogLevel::WARNING:  return "\033[33mWARNING";
        case LogLevel::ERROR: return "\033[31mERROR";
        case LogLevel::FATAL: return "\033[1;41mFATAL";
        default: return "UNKNOWN";
    }
}

LogLevel Logger::currentLevel = LogLevel::DEBUG;

}
