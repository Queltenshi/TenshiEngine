#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"
#include "TenshiEngine/Engine/Entity/Entity.hpp"
#include <string>
#include <iostream>

namespace te{

enum class LogLevel{DEBUG, INFO, WARNING, ERROR, FATAL};

/**
 * @brief Logger for logging messages
 *
 * Logs messages depending on the currentLevel in different colors
 */
class Logger{

public:
    Logger()=delete;
    Logger(const Logger&)=delete;
    Logger(Logger&&)=delete; 

    static LogLevel currentLevel;

    ///Use LOG_DEBUG or LOG_DEBUG_COMPONENT_CHANGED instead to automatically check if currentLevel is debug
    static void debug(const std::string &source, const std::string &message);

    ///Use LOG_DEBUG or LOG_DEBUG_COMPONENT_CHANGED instead to automatically check if currentLevel is debug
    static void debug(const std::string &source, const std::string &componentName, const components::Component *component, const EntityID entityID);

    /**
     * @brief Logs warning
     *
     * Logs warning message in yellow color 
     *
     * @param source Name of message sender
     * @param message Message to log
     */
    static void warning(const std::string &source, const std::string &message);

    /**
     * @brief Logs error
     *
     * Logs error message in red color 
     *
     * @param source Name of message sender
     * @param message Message to log
     */
    static void error(const std::string &source, const std::string &message);

    /**
     * @brief Logs info
     *
     * Logs info message in green color 
     *
     * @param source Name of message sender
     * @param message Message to log
     */
    static void info(const std::string &source, const std::string &message);

    /**
     * @brief Logs critical
     *
     * Logs critical message in white color and red background
     *
     * @param source Name of message sender
     * @param message Message to log
     */
    static void critical(const std::string &source, const std::string &message);

private:
    static void log(LogLevel logLevel, const std::string &system, const std::string &message);
    static std::string toString(LogLevel logLevel);
};

}


/** 
 * @defgroup LoggingMacros Logging Macros
 * Macros used for logging messages at different log levels.
 * @{
 */

/**
 * \def LOG_DEBUG(source, message)
 * \brief Logs a debug message
 *
 * Logs a debug message if the currentLevel is set to DEBUG
 * \param source The source or module where the log originates
 * \param message The message to log
 */
#define LOG_DEBUG(source, message) \
    do { \
        if (te::Logger::currentLevel == te::LogLevel::DEBUG) { \
            te::Logger::debug(source, message); \
        } \
    } while(0)

/**
 * \def LOG_DEBUG_COMPONENT_CHANGED(source, componentName, component, entityID)
 * \brief Logs a debug message when a component is changed
 *
 * Logs a debug message if the currentLevel is set to DEBUG
 * and when a compontent is changed
 * \param source The source or module where the log originates
 * \param componentName Name of changed component
 * \param component changed component
 * \param entityID ID of entity which component was changed
 */
#define LOG_DEBUG_COMPONENT_CHANGED(source, componentName, component, entityID) \
    do { \
        if (te::Logger::currentLevel == te::LogLevel::DEBUG) { \
            te::Logger::debug(source, componentName, component, entityID); \
        } \
    } while(0)
/** @} */

