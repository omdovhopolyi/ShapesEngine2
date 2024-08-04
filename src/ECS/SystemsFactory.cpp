#include "SystemsFactory.h"
#include "Logger/Logger.h"
#include "Utils/Assert.h"
#include <format>

namespace shen
{
    void SystemsFactory::RegisterSystemsFactory(const std::string& id, const FactoryFunc& factory)
    {
        auto [it, isRegistered] = _factories.insert({ id, factory });
        if (!isRegistered)
        {
            Logger::Log("[SystemsFactory::RegisterSystemFactory] Can not register system factory {}", id);
        }
    }

    std::unique_ptr<System> SystemsFactory::Get(const std::string& id)
    {
        if (auto it = _factories.find(id); it != _factories.end())
        {
            return it->second();
        }

        Assert(false, std::format("[SystemsFactory::RegisterSystemFactory] No factory for type '{}'", id));
        return nullptr;
    }
}