#pragma once

#include <string>
#include <vector>

namespace shen
{
    std::string EnumToString(const std::vector<std::string>& enumStr, int index);
    int EnumFromString(const std::vector<std::string>& enumStr, const std::string& str);
}
