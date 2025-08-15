#include "TenshiEngine/Engine/Core/Logger.hpp"
#include <string>

namespace te{

void Logger::log(LogLevel logLevel, const std::string &system, const std::string &message){
    std::cout << "[" + system + "] " + toString(logLevel) + ": " + message << std::endl;;  
}

void Logger::debug(const std::string &source, const std::string &message){
    if(Logger::currentLevel == LogLevel::DEBUG){
        log(LogLevel::DEBUG, source, message);
    }
}

}
