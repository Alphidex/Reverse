/**
 * @file Logger.cpp
 * @brief Implementation of the logging system
 */

#include "header/Logger.h"

// ANSI color codes for console output
#define COLOR_RESET   "\033[0m"
#define COLOR_DEBUG   "\033[36m"  // Cyan
#define COLOR_INFO    "\033[32m"  // Green
#define COLOR_WARNING "\033[33m"  // Yellow
#define COLOR_ERROR   "\033[31m"  // Red

Logger::Logger() 
    : minLogLevel(LogLevel::DEBUG)
    , fileLoggingEnabled(false)
    , useColors(true) {
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    minLogLevel = level;
}

void Logger::enableFileLogging(bool enable, const std::string& filepath) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    if (enable) {
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.open(filepath, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Failed to open log file: " << filepath << std::endl;
            fileLoggingEnabled = false;
            return;
        }
        fileLoggingEnabled = true;
    } else {
        if (logFile.is_open()) {
            logFile.close();
        }
        fileLoggingEnabled = false;
    }
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::log(LogLevel level, const std::string& message) {
    // Filter based on log level
    if (level < minLogLevel) {
        return;
    }

    std::lock_guard<std::mutex> lock(logMutex);

    std::string timestamp = getTimestamp();
    std::string levelStr = levelToString(level);
    
    // Format: [TIMESTAMP] [LEVEL] Message
    std::ostringstream oss;
    oss << "[" << timestamp << "] [" << levelStr << "] " << message;
    std::string formattedMessage = oss.str();

    // Console output with colors
    if (useColors) {
        std::cout << levelToColor(level) << formattedMessage << COLOR_RESET << std::endl;
    } else {
        std::cout << formattedMessage << std::endl;
    }

    // File output (without colors)
    if (fileLoggingEnabled && logFile.is_open()) {
        logFile << formattedMessage << std::endl;
        logFile.flush(); // Ensure immediate write
    }
}

std::string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO ";
        case LogLevel::WARNING: return "WARN ";
        case LogLevel::ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}

std::string Logger::levelToColor(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG:   return COLOR_DEBUG;
        case LogLevel::INFO:    return COLOR_INFO;
        case LogLevel::WARNING: return COLOR_WARNING;
        case LogLevel::ERROR:   return COLOR_ERROR;
        default:                return COLOR_RESET;
    }
}

std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    
    return oss.str();
}
