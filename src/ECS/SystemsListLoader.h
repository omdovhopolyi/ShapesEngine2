#pragma once

#include <vector>
#include <string>

namespace shen
{
    class SystemsListLoader
    {
    public:
        bool Load();
        const std::vector<std::string>& GetSystemsList() const;

    private:
        std::vector<std::string> _systemsList;
    };
}
