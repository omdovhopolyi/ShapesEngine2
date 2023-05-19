#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

const std::string RESET = "\033[0m";
const std::string RED = "\x1B[31m";
const std::string GREEN = "\x1B[32m";
const std::string YELLOW = "\033[33m";

namespace ShE
{
    std::vector<LogEntry> Logger::messages;

    void Logger::Log(const std::string& msg)
    {
        LogEntry logEntry;
        logEntry.type = LogType::Info;
        logEntry.message = "LOG | " + PrintDateTime() + ' ' + msg;

        std::cout << GREEN << logEntry.message << RESET << std::endl;

        messages.push_back(logEntry);
    }

    void Logger::Err(const std::string& msg)
    {
        LogEntry logEntry;
        logEntry.type = LogType::Error;
        logEntry.message = "ERR | " + PrintDateTime() + ' ' + msg;

        std::cout << RED << logEntry.message << RESET << std::endl;

        messages.push_back(logEntry);
    }

    std::string Logger::PrintDateTime()
    {
        std::stringstream ss;
        auto currentTime = std::chrono::system_clock::now();
        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
        std::tm* localTime = std::localtime(&currentTime_t);
        ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
}
