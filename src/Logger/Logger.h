#pragma once

#include <string>
#include <vector>
#include "spdlog/spdlog.h"
//#include "spdlog/sinks/ringbuffer_sink.h"

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
        static Logger& Instance();

        static void Log(const std::string& msg);
        static void Err(const std::string& msg);

        template<typename... Args>
        static void Log(const std::string& format, Args&& ...args)
        {
            Instance().GetLogger()->info(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Err(const std::string& format, Args&& ...args)
        {
            Instance().GetLogger()->error(format, std::forward<Args>(args)...);
        }

    private:
        Logger();

        spdlog::logger* GetLogger() const { return _logger.get(); }

    private:
        std::unique_ptr<spdlog::logger> _logger;
        std::vector<LogEntry> _messages;
    };
}
