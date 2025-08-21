#include "TenshiEngine/Engine/Core/Logger.hpp"
#include <string>

namespace te{

void Logger::log(LogLevel logLevel, const std::string &system, const std::string &message){
    std::cout << "[" + system + "] " + toString(logLevel) + ": " + message << std::endl;;  
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
    log(LogLevel::CRITICAL, source, message);
}
}
