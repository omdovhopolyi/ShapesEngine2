#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_sinks.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/ringbuffer_sink.h"

namespace shen
{
    Logger::Logger()
    {
        constexpr size_t buffer_size = 8192;
        auto ringbufferSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(buffer_size);
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true); // TODO filepath

        _logger = std::make_unique<spdlog::logger>("logger", spdlog::sinks_init_list{ consoleSink, fileSink, ringbufferSink });
        _logger->set_pattern("[%Y-%m-%d %H:%M:%S.%f %z] [%^%l%$] %v");
    }

    Logger& Logger::Instance()
    {
        static Logger inst;
        return inst;
    }

    void Logger::Log(const std::string& msg)
    {
        Instance().Log("{}", msg);
    }

    void Logger::Warn(const std::string& msg)
    {
        Instance().Warn("{}", msg);
    }

    void Logger::Err(const std::string& msg)
    {
        Instance().Err("{}", msg);
    }
}
