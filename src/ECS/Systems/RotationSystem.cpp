#include "RotationSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void RotationSystem::Update()
    {
        auto& world = _systems->GetWorld();
        world.Each<Rotator, Transform>([](const auto entity, const Rotator& rotator, Transform& transform)
        {
            transform.rotation = rotator.rotation;
        });
    }
}
