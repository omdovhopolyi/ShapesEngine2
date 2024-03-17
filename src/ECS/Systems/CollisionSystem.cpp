#pragma once

#include "CollisionSystem.h"
#include "ECS/Entity.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "Game/ManagersProvider.h"
#include "Logger/Logger.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/CollisionEvent.h"

namespace shen
{
    struct ObjectData
    {
        Entity entity;
        glm::vec3 pos;
        glm::vec3 size;
    };

    void CollisionSystem::Update()
    {
        //TODO rework. Temporary implementation

        /*auto world = ManagersProvider::Instance().GetWorld();
        const int amount = world->Size<BoundingBox>();

        std::vector<ObjectData> objects;
        objects.reserve(amount);

        world->Each<BoundingBox, Transform>(
            [&](auto entity, const BoundingBox& bb, const Transform& transform)
        {
            objects.push_back({
                entity,
                transform.position + bb.offset,
                bb.size * transform.scale
            });
        });

        for (size_t i = 0; i < objects.size(); i++)
        {
            for (size_t j = i + 1; j < objects.size(); j++)
            {
                auto a = objects[i];
                auto b = objects[j];

                if (a.pos.x <= b.pos.x + b.size.x &&
                    a.pos.x + a.size.x >= b.pos.x &&
                    a.pos.y <= b.pos.y + b.size.y &&
                    a.pos.y + a.size.y >= b.pos.y)
                {
                    CollisionEvent event(a.entity, b.entity);
                    ManagersProvider::Instance().GetMessenger()->Broadcast<CollisionEvent>(event);
                }
            }
        }*/
    }
}
