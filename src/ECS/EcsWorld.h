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

        template<class... Types>
        Entity GetFirst();

        template<class Comp, class... Args>
        Comp* AddComponent(Entity entity, Args... args);

        template<class Comp>
        Comp* GetComponent(Entity entity);

        template<class Comp, class... Args>
        Comp* GetOrCreateComponent(Entity entity, Args... args);

        std::vector<std::string> GetAllComponents(Entity entity);

        template<class Comp>
        void RemoveComponent(Entity entity);

        template<class Comp>
        bool HasComponent(Entity entity);

        template<class Comp, class Pred>
        void Sort(const Pred& pred);

        template<class Comp>
        int Size() const;

        Entity CreateEntity();
        bool IsValid(Entity entity);
        void DestroyEntity(Entity entity);
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

    template<class... Types>
    Entity EcsWorld::GetFirst()
    {
        auto view = _registry.view<Types...>();
        return view.front();
    }

    template<class Comp, class... Args>
    Comp* EcsWorld::AddComponent(Entity entity, Args... args)
    {
        Logger::Log("Adding {} compoenent to entity {}", typeid(Comp).name(), entity.GetId());

        if constexpr (std::is_empty_v<Comp>)
        {
            _registry.emplace<Comp>(entity._entity, std::forward<Args>(args)...);
            return nullptr;
        }
        else
        {
            return &_registry.emplace<Comp>(entity._entity, std::forward<Args>(args)...);
        }
    }

    template<class Comp>
    Comp* EcsWorld::GetComponent(Entity entity)
    {
        if (HasComponent<Comp>(entity))
        {
            return _registry.try_get<Comp>(entity._entity);
        }
        return nullptr;
    }

    template<class Comp, class... Args>
    Comp* EcsWorld::GetOrCreateComponent(Entity entity, Args... args)
    {
        if (HasComponent<Comp>(entity))
        {
            return _registry.try_get<Comp>(entity._entity);
        }
        else
        {
            return AddComponent<Comp>(entity._entity, std::forward<Args>(args)...);
        }
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
        auto view = _registry.view<Comp>();
        return view.contains(entity.GetEntity());
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
