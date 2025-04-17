#pragma once

#include "BaseSystems/System.h"
#include "ECS/Entity.h"
#include "ECS/SystemsManager.h"
#include "Serialization/DataElementWrapper.h"
#include <string>
#include <map>
#include <functional>

namespace shen
{
    struct LoadSaveFuncs
    {
        std::function<void(Entity, const DataElementWrapper&)> loadFunc;
        std::function<void(Entity, DataElementWrapper&)> saveFunc;
    };

    class MapLoaderSystem
        : public System
    {
        SYSTEMS_FACTORY(MapLoaderSystem)

    public:
        void Init(SystemsManager* systems) override;

        void LoadMap(const std::string& mapId) const;
        void LoadMap(DataElementWrapper& element, const std::string& mapId) const;
        void LoadComponents(Entity entity, const DataElementWrapper& element) const;
        Entity CreateEntityAndLoadComponents(const DataElementWrapper& element) const;
        Entity InstantiateAsset(const std::string& assetId) const;

        template<class T>
        void RegisterLoader(const std::string& id);

    private:
        void RegisterLoaders();
        void InstantiateAsset(Entity entity, const DataElementWrapper& element) const;

    private:
        std::unordered_map<std::string, LoadSaveFuncs> _functions;
    };

    template<class T>
    void MapLoaderSystem::RegisterLoader(const std::string& id)
    {
        auto& functions = _functions[id];

        functions.loadFunc = [&](Entity entity, const DataElementWrapper& element)
        {
            auto& world = _systems->GetWorld();
            if (auto comp = world.AddComponent<T>(entity))
            {
                T::Load(*comp, element);
            }
        };

        functions.saveFunc = [&](Entity entity, DataElementWrapper& element)
        {
            auto& world = _systems->GetWorld();
            if (auto comp = world.GetOrCreateComponent<T>(entity))
            {
                T::Save(*comp, element);
            }  
        };
    }
}
