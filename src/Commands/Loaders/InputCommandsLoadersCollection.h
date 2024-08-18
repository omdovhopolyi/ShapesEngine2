#pragma once

#include "Utils/Singleton.h"
#include <map>
#include <string>
#include <memory>

namespace shen
{
    class InputCommandLoader;

    class InputCommandsLoadersCollection
        : public Singleton<InputCommandsLoadersCollection>
    {
    public:
        template<class LoaderType>
        void Register(const std::string& type)
        {
            _loaders[type] = std::make_unique<LoaderType>();
        }

        InputCommandLoader* GetLoader(const std::string& type) const;

    private:
        std::map<std::string, std::unique_ptr<InputCommandLoader>> _loaders;
    };
}
