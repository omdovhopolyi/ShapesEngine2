#pragma once

#include "ECS/SystemsFactoryRegistration.h"
#include <typeindex>
#include <string>

namespace shen
{
    class SystemsManager;

    class System
    {
    public:
        virtual ~System() = default;

        virtual void Init(SystemsManager* systems);
        virtual void Load() {}
        virtual void Start() {}
        virtual void Save() {}
        virtual void Stop() {}

        virtual std::type_index GetTypeIndex() { return std::type_index(typeid(System)); }
        virtual std::string GetTypeName() { return {}; }

        SystemsManager* GetSystems() const { return _systems; }

    protected:
        SystemsManager* _systems = nullptr;
    };
}
