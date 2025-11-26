#ifndef LOG_OUTPUT_PATH
#define LOG_OUTPUT_PATH "application.log"
#endif

#include "log.h"
#include <fstream>
#include <iostream>
#include <ctime>

Log::Log() {
    logFile.open(LOG_OUTPUT_PATH, std::ios::app);
}
Log::~Log() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
Log& Log::getInstance() {
    static Log instance;
    return instance;
}
void Log::debug(const std::string &message) {
    Log &logger = getInstance();
    if (logger.logFile.is_open()) {
        logger.logFile << "[DEBUG] " << message << std::endl;
    }
}
void Log::info(const std::string &message) {
    Log &logger = getInstance();
    if (logger.logFile.is_open()) {
        logger.logFile << "[INFO] " << message << std::endl;
    }
}
void Log::warning(const std::string &message) {
    Log &logger = getInstance();
    if (logger.logFile.is_open()) {
        logger.logFile << "[WARNING] " << message << std::endl;
    }
}
void Log::error(const std::string &message) {
    Log &logger = getInstance();
    if (logger.logFile.is_open()) {
        logger.logFile << "[ERROR] " << message << std::endl;
    }
}