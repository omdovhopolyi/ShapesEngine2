#include "EcsWorld.h"

namespace shen
{
    std::vector<std::string> EcsWorld::GetAllComponents(Entity entity)
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

    Entity EcsWorld::CreateEntity()
    {
        return { _registry.create() };
    }

    bool EcsWorld::IsValid(Entity entity)
    {
        return _registry.valid(entity.GetEntity());
    }

    void EcsWorld::DestroyEntity(Entity entity)
    {
        _registry.destroy(entity.GetEntity());
    }

    void EcsWorld::Clear()
    {
        _registry.clear();
    }
}
