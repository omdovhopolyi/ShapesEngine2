#pragma once

#include "Systems/System.h"
#include "Systems/RenderSystem.h"
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

        template<class T>
        void RegisteSystem();

        template<class T>
        void RegisterRenderSystem();

        template <class T>
        T* GetSystem() const;

        void Start();
        void Update();
        void Draw();
        void Stop();
        void Clear();

    private:
        std::vector<std::unique_ptr<System>> _systems;
        std::vector<std::unique_ptr<RenderSystem>> _renderSystems;
        std::map<std::type_index, BaseSystem*> _mappedSystems;
    };

    template <class T>
    void SystemsManager::RegisteSystem()
    {
        _systems.push_back(std::make_unique<T>());
        _mappedSystems[std::type_index(typeid(T))] = _systems.back().get();
        Logger::Log("Register {} system", typeid(T).name());
    }

    template<class T>
    void SystemsManager::RegisterRenderSystem()
    {
        if (std::is_base_of_v<RenderSystem, T>)
        {
            _renderSystems.push_back(std::make_unique<T>());
            _mappedSystems[std::type_index(typeid(T))] = _renderSystems.back().get();
            Logger::Log("Register {} render system", typeid(T).name());
        }
        else
        {
            // TODO assert
        }
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
