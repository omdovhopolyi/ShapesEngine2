#pragma once

#include <vector>
#include <string>

namespace shen
{
    enum class SpriteType
    {
        OneType,
        AnotherType
    };

    static std::vector<std::string> SpriteTypeStr = {
        "Type",
        "AnotherType"
    };
}
