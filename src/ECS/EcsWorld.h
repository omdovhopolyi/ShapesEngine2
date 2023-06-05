#pragma once

#include "Utils/Singleton.h"

#include <entt/entt.hpp>

namespace shen
{
    using Entity = entt::entity;

    class EcsWorld
        : public Singleton<EcsWorld>
    {
    public:
        template<class... Types, class Func>
        void Each(Func& func)
        {
            auto view = _registry.view<Types...>();
            view.each(func);
        }
        
        template<class Comp, class... Args>
        Comp& AddComponent(Entity entity, Args... args)
        {
            return _registry.emplace<Comp>(entity, std::forward<Args>(args)...);
        }

        Entity CreateEntity();
        void Clear();

    private:
        entt::registry _registry;
    };
}
