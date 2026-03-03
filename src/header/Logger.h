/**
 * @file Logger.h
 * @brief Centralized logging system for the Reverse Engine
 * @details Provides leveled logging with timestamps and optional file output
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <mutex>

/**
 * @brief Log severity levels
 */
enum class LogLevel {
    DEBUG = 0,   ///< Verbose debugging information
    INFO = 1,    ///< General informational messages
    WARNING = 2, ///< Warning messages (non-critical issues)
    ERROR = 3    ///< Error messages (critical issues)
};

/**
 * @brief Centralized logging system with timestamps and level filtering
 * @details Singleton logger that supports console and file output with configurable log levels
 */
class Logger {
public:
    /**
     * @brief Gets the singleton Logger instance
     * @return Reference to the Logger instance
     */
    static Logger& getInstance();

    /**
     * @brief Sets the minimum log level to display
     * @param level Minimum level (messages below this are filtered out)
     */
    void setLogLevel(LogLevel level);

    /**
     * @brief Enables or disables file logging
     * @param enable True to enable file output
     * @param filepath Path to log file (default: "reverse.log")
     */
    void enableFileLogging(bool enable, const std::string& filepath = "reverse.log");

    /**
     * @brief Logs a debug message
     * @param message Message to log
     */
    void debug(const std::string& message);

    /**
     * @brief Logs an info message
     * @param message Message to log
     */
    void info(const std::string& message);

    /**
     * @brief Logs a warning message
     * @param message Message to log
     */
    void warning(const std::string& message);

    /**
     * @brief Logs an error message
     * @param message Message to log
     */
    void error(const std::string& message);

    /**
     * @brief Generic log function with explicit level
     * @param level Log level
     * @param message Message to log
     */
    void log(LogLevel level, const std::string& message);

    // Delete copy constructor and assignment operator (singleton)
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();  ///< Private constructor (singleton)
    ~Logger(); ///< Destructor closes file if open

    /**
     * @brief Gets string representation of log level
     * @param level Log level
     * @return String representation
     */
    std::string levelToString(LogLevel level) const;

    /**
     * @brief Gets ANSI color code for log level (console output)
     * @param level Log level
     * @return ANSI color code string
     */
    std::string levelToColor(LogLevel level) const;

    /**
     * @brief Gets current timestamp as formatted string
     * @return Timestamp string
     */
    std::string getTimestamp() const;

    LogLevel minLogLevel;        ///< Minimum log level to display
    bool fileLoggingEnabled;     ///< Whether file logging is enabled
    std::ofstream logFile;       ///< Output file stream
    std::mutex logMutex;         ///< Mutex for thread-safe logging
    bool useColors;              ///< Whether to use ANSI colors in console
};

// Convenience macros for easier logging
#ifdef NDEBUG
    // In release builds, disable DEBUG logging
    #define LOG_DEBUG(msg) ((void)0)
#else
    #define LOG_DEBUG(msg) Logger::getInstance().debug(msg)
#endif

#define LOG_INFO(msg)    Logger::getInstance().info(msg)
#define LOG_WARNING(msg) Logger::getInstance().warning(msg)
#define LOG_ERROR(msg)   Logger::getInstance().error(msg)
