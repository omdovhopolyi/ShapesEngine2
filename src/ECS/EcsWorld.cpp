#include "EcsWorld.h"

namespace shen
{
    Entity EcsWorld::CreateEntity()
    {
        return _registry.create();
    }

    void EcsWorld::Clear()
    {
        _registry.clear();
    }
}
