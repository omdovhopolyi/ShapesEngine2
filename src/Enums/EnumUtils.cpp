#include "EnumUtils.h"

namespace shen
{
    std::string EnumToString(const std::vector<std::string>& enumStr, int index)
    {
        if (index >= 0 && index < static_cast<int>(enumStr.size()))
        {
            return enumStr[index];
        }

        return {};
    }

    int EnumFromString(const std::vector<std::string>& enumStr, const std::string& str)
    {
        for (int i = 0; i < static_cast<int>(enumStr.size()); ++i)
        {
            if (enumStr[i] == str)
            {
                return i;
            }
        }

        return -1;
    }
}
