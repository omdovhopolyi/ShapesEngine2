#pragma once

#include "BaseSystems/System.h"
#include "ECS/Entity.h"
#include "ECS/SystemsManager.h"
#include "Serialization/Serialization.h"
#include <tinyxml2/tinyxml2.h>
#include <string>
#include <map>
#include <functional>

namespace shen
{
    struct LoadSaveFuncs
    {
        std::function<void(Entity, tinyxml2::XMLElement*)> loadFunc;
        std::function<void(Serialization&)> saveFunc;
    };

    class MapLoaderSystem
        : public System
    {
    public:
        void Init(SystemsManager* systems) override;
        void Start() override;

    private:
        void RegisterLoaders();
        void LoadMap(const std::string& mapId);

        template<class T>
        void RegisterLoader(const std::string& id);

    private:
        std::map<std::string, LoadSaveFuncs> _functions;
    };

    template<class T>
    void MapLoaderSystem::RegisterLoader(const std::string& id)
    {
        auto& functions = _functions[id];

        functions.loadFunc = [&](Entity entity, tinyxml2::XMLElement* element)
        {
            auto& world = _systems->GetWorld();
            auto comp = world.AddComponent<T>(entity);
            Serialization serialization(_systems, element);
            T::Load(*comp, serialization);
        };

        functions.saveFunc = T::Save;
    }
}
