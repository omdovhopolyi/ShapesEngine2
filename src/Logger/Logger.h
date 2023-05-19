#pragma once

#include <string>
#include <vector>

namespace ShE
{
    enum class LogType
    {
        Info,
        Warning,
        Error
    };

    struct LogEntry
    {
        LogType type;
        std::string message;
    };

    class Logger
    {
    public:
        static void Log(const std::string& msg);
        static void Err(const std::string& msg);
        static std::string PrintDateTime();

    public:
        static std::vector<LogEntry> messages;
    };
}
