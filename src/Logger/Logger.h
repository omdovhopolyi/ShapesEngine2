#pragma once

#include <string>
#include <vector>
#include "spdlog/spdlog.h"

namespace shen
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
        static void Warn(const std::string& msg);
        static void Err(const std::string& msg);

        template<typename... Args>
        static void Log(const std::string& format, Args&& ...args)
        {
            Instance().GetLogger()->info(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }

        template<typename... Args>
        static void Warn(const std::string& format, Args&& ...args)
        {
            Instance().GetLogger()->warn(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }

        template<typename... Args>
        static void Err(const std::string& format, Args&& ...args)
        {
            Instance().GetLogger()->error(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }

    private:
        Logger();

        spdlog::logger* GetLogger() const { return _logger.get(); }

    private:
        std::unique_ptr<spdlog::logger> _logger;
        std::vector<LogEntry> _messages;
    };
}
