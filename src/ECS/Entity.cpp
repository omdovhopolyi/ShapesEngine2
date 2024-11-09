#include "Entity.h"

namespace shen
{
    Entity::Entity(const entt::entity& entity)
        : _entity(entity)
    { }

    Entity::Entity(std::uint32_t index)
        : _entity(static_cast<entt::entity>(index))
    {}

    std::uint32_t Entity::GetId() const
    {
        return static_cast<uint32_t>(_entity);
    }

    int Entity::GetIdInt() const
    {
        return static_cast<int>(_entity);
    }
}
