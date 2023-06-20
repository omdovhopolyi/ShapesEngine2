#pragma once

#include "Systems/System.h"
#include "Logger/Logger.h"

#include <memory>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>

namespace shen
{
    class SystemsManager
    {
    public:
        void Init();

        template <class T>
        void RegisteSystem();

        template <class T>
        T* GetSystem() const;

        void Start();
        void Update();
        void Stop();
        void Clear();

    private:
        std::vector<std::unique_ptr<System>> _systems;
        std::map<std::type_index, System*> _mappedSystems;
    };

    template <class T>
    void SystemsManager::RegisteSystem()
    {
        _systems.push_back(std::make_unique<T>());
        _mappedSystems[std::type_index(typeid(T))] = _systems.back().get();
        Logger::Log("Register {} system", typeid(T).name());
    }

    template <class T>
    T* SystemsManager::GetSystem() const
    {
        const auto typeIndex = std::type_index(typeid(T));
        auto it = _mappedSystems.find(typeIndex);
        if (it != _mappedSystems.end())
        {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }
}
