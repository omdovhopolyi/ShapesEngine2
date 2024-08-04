#pragma once

#include "Systems/BaseSystems/System.h"
#include "Utils/Singleton.h"
#include <string>
#include <map>
#include <functional>
#include <memory>

namespace shen
{
    class System;

    class SystemsFactory
        : public Singleton<SystemsFactory>
    {
    public:
        using FactoryFunc = std::function<std::unique_ptr<System>()>;

        void RegisterSystemsFactory(const std::string& id, const FactoryFunc& factory);
        std::unique_ptr<System> Get(const std::string& id);

    private:
        std::map<std::string, FactoryFunc> _factories;
    };
}