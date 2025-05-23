#pragma once

#include <entt/entt.hpp>

namespace shen
{
    class Entity
    {
        friend class World;

    public:
        Entity() = default;
        Entity(const entt::entity& entity);
        Entity(std::uint32_t index);

        std::uint32_t GetId() const;
        int GetIdInt() const;

        bool operator == (const Entity& other) { return _entity == other._entity; }
        bool operator != (const Entity& other) { return _entity != other._entity; }
        bool operator < (const Entity& other) { return _entity < other._entity; }

        entt::entity GetEntity() const { return _entity; }

    private:
        entt::entity _entity = {};
    };
}
