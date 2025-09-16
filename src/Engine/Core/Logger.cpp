#include "TenshiEngine/Engine/Core/Logger.hpp"

namespace te{

void Logger::log(LogLevel logLevel, const std::string &source, const std::string &content){
    std::string logMessage = "[" + currentTime() + "] " + "[" + source + "] ";

    std::string consoleLog = logMessage + coloredMessage(logLevel, content);
    std::cout << consoleLog << std::endl;  

    std::string fileLog = logMessage = logMessage + message(logLevel, content);
    if(logLevel != LogLevel::DEBUG){
        std::ofstream logFile(logFileName, std::ios::app);
        logFile << fileLog + "\n";
        logFile.close();
    }
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

std::string Logger::currentTime(){
    time_t timestamp = time(0);
    struct tm *localTime = localtime(&timestamp);
    auto hour = std::to_string(localTime->tm_hour);
    auto min = std::to_string(localTime->tm_min);
    auto sec = std::to_string(localTime->tm_sec);

    std::ostringstream oStringStream;
    oStringStream << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
                  << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
                  << std::setfill('0') << std::setw(2) << localTime->tm_sec;

    return oStringStream.str();
}

std::string Logger::toString(LogLevel logLevel) {
    switch (logLevel) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

std::string Logger::coloredMessage(LogLevel logLevel, const std::string &content){
    std::string color;
    switch(logLevel){
        case LogLevel::DEBUG:
            color = "34m"; //Blue 
            break;
        case LogLevel::INFO:
            color = "32m"; //Green 
            break;
        case LogLevel::WARNING:
            color = "33m"; //Yellow
            break;
        case LogLevel::ERROR:
            color = "31m"; //Red 
            break;
        case LogLevel::FATAL:
            color = "1;41m"; //White, red background 
            break;
    }
    return "\033[" + color + toString(logLevel) + ": " + content + "\033[0m";
}

std::string Logger::message(LogLevel logLevel, const std::string &content){
    return toString(logLevel) + ": " + content;
}

bool Logger::debugMode = false;

const std::string Logger::logFileName = "Game.log";

Logger::ClearLog Logger::clearLog;

}
