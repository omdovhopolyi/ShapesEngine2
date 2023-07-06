#pragma once

#include "Entity.h"
#include "Logger/Logger.h"
#include <entt/entt.hpp>

namespace shen
{
    class EcsWorld
    {
    public:
        template<class... Types, class Func>
        void Each(const Func& func);
        
        template<class Comp, class... Args>
        Comp& AddComponent(Entity entity, Args... args);

        template<class Comp>
        Comp& GetComponent(Entity entity);

        template<class Comp>
        void RemoveComponent(Entity entity);

        template<class Comp>
        bool HasComponent(Entity entity);

        template<class Comp, class Pred>
        void Sort(const Pred& pred);

        template<class Comp>
        int Size() const;

        Entity CreateEntity();
        void Clear();

    private:
        entt::registry _registry;
    };


    template<class... Types, class Func>
    void EcsWorld::Each(const Func& func)
    {
        auto view = _registry.view<Types...>();
        view.each(func);
    }

    template<class Comp, class... Args>
    Comp& EcsWorld::AddComponent(Entity entity, Args... args)
    {
        Logger::Log("Adding {} compoenent to entity {}", typeid(Comp).name(), entity.GetId());
        return _registry.emplace<Comp>(entity._entity, std::forward<Args>(args)...);
    }

    template<class Comp>
    Comp& EcsWorld::GetComponent(Entity entity)
    {
        return _registry.get<Comp>(entity._entity);
    }

    template<class Comp>
    void EcsWorld::RemoveComponent(Entity entity)
    {
        Logger::Log("Removing {} compoenent to entity {}", typeid(Comp).name(), entity.GetId());
        _registry.remove<Comp>(entity._entity);
    }

    template<class Comp>
    bool EcsWorld::HasComponent(Entity entity)
    {
        return _registry.get<Comp>(entity._entity) != nullptr;
    }

    template<class Comp, class Pred>
    void EcsWorld::Sort(const Pred& pred)
    {
        _registry.sort<Comp>(pred);
    }

    template<class Comp>
    int EcsWorld::Size() const
    {
        return static_cast<int>(_registry.storage<Comp>().size());
    }
}
