#include "EcsWorld.h"

namespace shen
{
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
