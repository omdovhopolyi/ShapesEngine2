#include "World.h"

namespace shen
{
    std::vector<std::string> World::GetAllComponents(Entity entity)
    {
        std::vector<std::string> result;

        for (auto&& [typeId, storage] : _registry.storage())
        {
            entt::type_info typeInfo = storage.type();

            if (storage.contains(entity.GetEntity()))
            {
                result.push_back(std::string{ typeInfo.name() });
            }
        }

        return result;
    }

    Entity World::CreateEntity()
    {
        return { _registry.create() };
    }

    bool World::IsValid(Entity entity)
    {
        return _registry.valid(entity.GetEntity());
    }

    void World::DestroyEntity(Entity entity)
    {
        _registry.destroy(entity.GetEntity());
    }

    void World::Clear()
    {
        _registry.clear();
    }
}
