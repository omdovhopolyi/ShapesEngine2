#pragma once

#include "ECS/World.h"
#include "Systems/BaseSystems/System.h"
#include "Systems/Basesystems/RenderSystem.h"
#include "Systems/BaseSystems/UpdateSystem.h"
#include "Logger/Logger.h"

#include <memory>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <format>

namespace shen
{
    class Game;

    class SystemsManager
    {
    public:
        void Init(Game* game);

        template<class T, class... Args>
        void RegisterSystem(Args... args);

        template <class T>
        T* GetSystem() const;

        void Start();
        void Update();
        void Draw();
        void Stop();
        void Clear();

        World& GetWorld() { return _world; }


    private:
        std::vector<std::unique_ptr<System>> _simpleSystems;
        std::vector<std::unique_ptr<UpdateSystem>> _updateSystems;
        std::vector<std::unique_ptr<RenderSystem>> _renderSystems;
        std::map<std::type_index, System*> _mappedSystems;
        std::vector<System*> _registrationOrderedSystems;
        World _world;
        Game* _game = nullptr;
    };

    template <class T, class... Args>
    void SystemsManager::RegisterSystem(Args... args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        system->Init(this);
        _mappedSystems[std::type_index(typeid(T))] = system.get();
        _registrationOrderedSystems.push_back(system.get());

        if constexpr (std::is_base_of_v<RenderSystem, T>)
        {
            _renderSystems.push_back(std::move(system));
            Logger::Log(std::format("Register {} render system", typeid(T).name()));
        }
        else if constexpr (std::is_base_of_v<UpdateSystem, T>)
        {
            _updateSystems.push_back(std::move(system));
            Logger::Log(std::format("Register {} update system", typeid(T).name()));
        }
        else
        {
            _simpleSystems.push_back(std::move(system));
            Logger::Log(std::format("Register {} simple system", typeid(T).name()));
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
