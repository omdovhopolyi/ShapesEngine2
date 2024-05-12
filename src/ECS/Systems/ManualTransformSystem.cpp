#include "ManualTransformSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include <box2d/box2d.h>

namespace shen
{
    void ManualTransformSystem::Update()
    {
        auto& world = _systems->GetWorld();

        world.Each<Mover, Transform>([&](auto entity, const Mover& mover, Transform& transform)
        {
            transform.position = mover.position;

            if (auto rb = world.GetComponent<RigidBody>(entity))
            {
                if (auto body = rb->body)
                {
                    const auto currentPos = body->GetPosition();
                    body->SetTransform(position, float angle);
                }
            }
        });

        world.Each<Rotator, Transform>([&](auto entity, const Rotator& rotator, Transform& transform)
        {

        });
    }
}
