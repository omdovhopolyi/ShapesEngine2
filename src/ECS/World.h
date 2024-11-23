#pragma once

#include "Entity.h"
#include "Logger/Logger.h"
#include <format>
#include <entt/entt.hpp>

namespace shen
{
    class World
    {
    public:
        template<class... Types, class Func>
        void Each(const Func& func);

        template<class... Types>
        Entity GetFirst();

        template<class Comp, class... Args>
        Comp* AddComponent(Entity entity, Args... args);

        template<class Comp, class... Args>
        Comp* AddOrSkipComponent(Entity entity, Args... args);

        template<class Comp, class... Args>
        Comp* AddOrReplaceComponent(Entity entity, Args... args);

        template<class Comp>
        Comp* GetComponent(Entity entity);

        template<class Comp, class... Args>
        Comp* GetOrCreateComponent(Entity entity, Args... args);

        std::vector<std::string> GetAllComponents(Entity entity);

        template<class Comp>
        void RemoveComponent(Entity entity);

        template<class Comp>
        void RemoveAllComponents();

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
    void World::Each(const Func& func)
    {
        auto view = _registry.view<Types...>();
        view.each(func);
    }

    template<class... Types>
    Entity World::GetFirst()
    {
        auto view = _registry.view<Types...>();
        return view.front();
    }

    template<class Comp, class... Args>
    Comp* World::AddComponent(Entity entity, Args... args)
    {
        Logger::Log(std::format("Adding {} compoenent to entity {}", typeid(Comp).name(), entity.GetId()));

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

    template<class Comp, class... Args>
    Comp* World::AddOrSkipComponent(Entity entity, Args... args)
    {
        if (!HasComponent<Comp>(entity))
        {
            return AddComponent<Comp>(entity, std::forward<Args>(args)...);
        }

        return GetComponent<Comp>(entity);
    }

    template<class Comp, class... Args>
    Comp* World::AddOrReplaceComponent(Entity entity, Args... args)
    {
        if (HasComponent<Comp>(entity))
        {
            RemoveComponent<Comp>(entity);
        }

        return AddComponent<Comp>(entity, std::forward<Args>(args)...);
    }

    template<class Comp>
    Comp* World::GetComponent(Entity entity)
    {
        if (HasComponent<Comp>(entity))
        {
            return _registry.try_get<Comp>(entity._entity);
        }
        return nullptr;
    }

    template<class Comp, class... Args>
    Comp* World::GetOrCreateComponent(Entity entity, Args... args)
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
    void World::RemoveComponent(Entity entity)
    {
        Logger::Log(std::format("Removing {} compoenent to entity {}", typeid(Comp).name(), entity.GetId()));
        _registry.remove<Comp>(entity._entity);
    }

    template<class Comp>
    void World::RemoveAllComponents()
    {
        _registry.clear<Comp>();
    }

    template<class Comp>
    bool World::HasComponent(Entity entity)
    {
        auto view = _registry.view<Comp>();
        return view.contains(entity.GetEntity());
    }

    template<class Comp, class Pred>
    void World::Sort(const Pred& pred)
    {
        _registry.sort<Comp>(pred);
    }

    template<class Comp>
    int World::Size() const
    {
        return static_cast<int>(_registry.storage<Comp>().size());
    }
}
