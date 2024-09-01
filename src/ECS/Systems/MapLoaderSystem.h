#pragma once

#include "BaseSystems/System.h"
#include "ECS/Entity.h"
#include "ECS/SystemsManager.h"
#include "Serialization/Serialization.h"
#include <string>
#include <map>
#include <functional>

namespace shen
{
    struct LoadSaveFuncs
    {
        std::function<void(Entity, const Serialization&)> loadFunc;
        std::function<void(Entity, Serialization&)> saveFunc;
    };

    class MapLoaderSystem
        : public System
    {
        SYSTEMS_FACTORY(MapLoaderSystem)

    public:
        void Init(SystemsManager* systems) override;
        void Start() override;

        template<class T>
        void RegisterLoader(const std::string& id);

    private:
        void RegisterLoaders();
        void LoadMap(const std::string& mapId);

    private:
        std::map<std::string, LoadSaveFuncs> _functions;
    };

    template<class T>
    void MapLoaderSystem::RegisterLoader(const std::string& id)
    {
        auto& functions = _functions[id];

        functions.loadFunc = [&](Entity entity, const Serialization& element)
        {
            auto& world = _systems->GetWorld();
            auto comp = world.AddComponent<T>(entity);
            T::Load(*comp, element);
        };

        functions.saveFunc = [&](Entity entity, Serialization& element)
        {
            auto& world = _systems->GetWorld();
            if (auto comp = world.GetComponent<T>(entity))
            {
                T::Save(*comp, element);
            }  
        };
    }
}
