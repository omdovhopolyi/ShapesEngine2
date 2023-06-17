#include "Entity.h"

namespace shen
{
    Entity::Entity(const entt::entity& entity)
        : _entity(entity)
    { }

    std::uint32_t Entity::GetId() const
    {
        return static_cast<uint32_t>(_entity);
    }
}
