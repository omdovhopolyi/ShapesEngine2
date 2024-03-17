#pragma once

#include "ECS/Entity.h"

#include <string>
#include <map>
#include <functional>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class EcsWorld;

    struct LoadSaveFuncs
    {
        std::function<void(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element)> loadFunc;
        std::function<void(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element)> saveFunc;
    };

    class MapLoader
    {
    public:
        void RegisterLoaders();
        void LoadMap(const std::string& mapId);

        template<class T>
        void RegisterLoader(const std::string& id);

    private:
        std::map<std::string, LoadSaveFuncs> _functions;
    };

    template<class T>
    void MapLoader::RegisterLoader(const std::string& id)
    {
        _functions[id] = { T::Load, T::Save };
    }
}
