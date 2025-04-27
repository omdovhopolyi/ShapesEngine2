#pragma once

#include <map>
#include <any>
#include <string>

namespace shen
{
    class Storage
    {
    public:
        bool SetVar(const std::string& key, const std::any& var);

        template<class T>
        const T* GetVar(const std::string& key) const;

        bool HasVar(const std::string& key) const;

    private:
        std::map<std::string, std::any> _vars;
    };

    template<class T>
    const T* Storage::GetVar(const std::string& key) const
    {
        if (auto it = _vars.find(key); it != _vars.end())
        {
            return std::any_cast<const T>(&it->second);
        }

        return nullptr;
    }
}
