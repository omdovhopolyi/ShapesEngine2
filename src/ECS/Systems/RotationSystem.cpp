#include "RotationSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "Utils/Math.h"
#include <box2d/box2d.h>

namespace shen
{
    void RotationSystem::Update()
    {
        auto& world = _systems->GetWorld();
        world.Each<Rotator, Transform>([&](const auto entity, const Rotator& rotator, Transform& transform)
        {
            transform.rotation = rotator.rotation;

            if (auto rb = world.GetComponent<RigidBody>(entity))
            {
                if (rb->body)
                {
                    const auto currentPos = rb->body->GetPosition();
                    rb->body->SetTransform(currentPos, Radians(rotator.rotation));
                }
            }
        });
    }
}
