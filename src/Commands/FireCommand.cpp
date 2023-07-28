#include "FireCommand.h"

#include "Game/ManagersProvider.h"
#include "Resources/SDLTexturesManager.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"

namespace shen
{
    void FireCommand::Execute(const Entity& entity) const
    {
        auto world = ManagersProvider::Instance().GetWorld();
        auto assetsManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();

        auto transform = world->GetComponent<Transform>(entity);
        auto bb = world->GetComponent<BoundingBox>(entity);

        if (world->IsValid(entity))
        {
            auto bullet = world->CreateEntity();
            world->AddComponent<Bullet>(bullet);
            world->AddComponent<Transform>(bullet, transform->position, 0.f, glm::vec3(1.f, 1.f, 1.f));
            world->AddComponent<RigidBody>(bullet, glm::vec3(200.f, 0.f, 0.f));
            world->AddComponent<SDLSprite>(bullet, assetsManager->GetAsset("bullet"), 4, 4, 0, 0, 4, 4);
        }
    }
}
