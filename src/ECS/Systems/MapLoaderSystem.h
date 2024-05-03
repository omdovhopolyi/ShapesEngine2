#pragma once

#include "BaseSystems/System.h"
#include "ECS/Entity.h"
#include <tinyxml2/tinyxml2.h>
#include <string>
#include <map>
#include <functional>

namespace shen
{
    class World;

    struct LoadSaveFuncs
    {
        std::function<void(Entity entity, World& world, const tinyxml2::XMLElement* element)> loadFunc;
        std::function<void(Entity entity, World& world, tinyxml2::XMLElement* element)> saveFunc;
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
        _functions[id] = { T::Load, T::Save };
    }
}
