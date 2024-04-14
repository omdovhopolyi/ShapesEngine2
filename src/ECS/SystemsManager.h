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

namespace shen
{
    class Game;

    class SystemsManager
    {
    public:
        void Init(Game* game);

        template<class T>
        void RegisterSystem();

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

    template <class T>
    void SystemsManager::RegisterSystem()
    {
        if constexpr (std::is_base_of_v<RenderSystem, T>)
        {
            _renderSystems.push_back(std::make_unique<T>());
            _renderSystems.back()->Init(this);
            _mappedSystems[std::type_index(typeid(T))] = _renderSystems.back().get();
            _registrationOrderedSystems.push_back(_renderSystems.back().get());
            Logger::Log("Register {} render system", typeid(T).name());
        }
        else if constexpr (std::is_base_of_v<UpdateSystem, T>)
        {
            _updateSystems.push_back(std::make_unique<T>());
            _updateSystems.back()->Init(this);
            _mappedSystems[std::type_index(typeid(T))] = _updateSystems.back().get();
            _registrationOrderedSystems.push_back(_renderSystems.back().get());
            Logger::Log("Register {} update system", typeid(T).name());
        }
        else
        {
            _simpleSystems.push_back(std::make_unique<T>());
            _simpleSystems.back()->Init(this);
            _mappedSystems[std::type_index(typeid(T))] = _updateSystems.back().get();
            _registrationOrderedSystems.push_back(_renderSystems.back().get());
            Logger::Log("Register {} simple system", typeid(T).name());
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
