#include <entt/entt.hpp>

namespace shen
{
    class Entity
    {
        friend class EcsWorld;

    public:
        Entity(const entt::entity& entity);

        std::uint32_t GetId() const;

        bool operator == (const Entity& other) { return _entity == other._entity; }
        bool operator < (const Entity& other) { return _entity < other._entity; }

    private:
        entt::entity _entity;
    };
}
