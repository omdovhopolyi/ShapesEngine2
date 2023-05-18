#pragma once

#include <string>

namespace ShE
{
    class Logger
    {
    public:
        static void Log(const std::string& msg);
        static void Err(const std::string& msg);
        static std::string PrintDateTime();
    };
}
