#pragma once

#include <vector>
#include <string>
#include <sstream>

#define SHEN_ENUM(name, ...)                                                                        \
    enum class name { __VA_ARGS__ };                                                                \
    class name##EnumTraits                                                                          \
    {                                                                                               \
    public:                                                                                         \
        name##EnumTraits(const char* str)                                                           \
        {                                                                                           \
            std::stringstream ss(str);                                                              \
            std::string token;                                                                      \
                                                                                                    \
            while (std::getline(ss, token, ','))                                                    \
            {                                                                                       \
                enumStrArray.push_back(token);                                                      \
                ss.get();                                                                           \
            }                                                                                       \
        }                                                                                           \
                                                                                                    \
        std::string ToString(name type)                                                             \
        {                                                                                           \
            const int typeIndex = static_cast<int>(type);                                           \
                                                                                                    \
            if (typeIndex >= 0 && typeIndex < static_cast<int>(enumStrArray.size()))                \
            {                                                                                       \
                return enumStrArray[typeIndex];                                                     \
            }                                                                                       \
                                                                                                    \
            return {};                                                                              \
        }                                                                                           \
                                                                                                    \
        name FromString(const std::string& str)                                                     \
        {                                                                                           \
            for (int i = 0; i < static_cast<int>(enumStrArray.size()); ++i)                         \
            {                                                                                       \
                if (enumStrArray[i] == str)                                                         \
                {                                                                                   \
                    return static_cast<name>(i);                                                    \
                }                                                                                   \
            }                                                                                       \
                                                                                                    \
            return static_cast<name>(0);                                                            \
        }                                                                                           \
                                                                                                    \
    private:                                                                                        \
        std::vector<std::string> enumStrArray;                                                      \
    };                                                                                              \
                                                                                                    \
    static name##EnumTraits name##Enum(#__VA_ARGS__);                                               