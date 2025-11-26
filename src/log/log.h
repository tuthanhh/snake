
#pragma once
#include <fstream>
#include <string>

class Log {
public: 
    static void debug(const std::string &message);
    static void info(const std::string &message);
    static void warning(const std::string &message);
    static void error(const std::string &message);
private:
    std::fstream logFile;
    Log(); 
    ~Log();
    static Log& getInstance();
};