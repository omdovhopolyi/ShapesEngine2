#include "WeaponManager.h"

#include "Game/WeaponManager.h"
#include "Game/ManagersProvider.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"
#include "Resources/SDLTexturesManager.h"

namespace shen
{
    void WeaponManager::FireBullet(Entity owner, glm::vec3 position, glm::vec3 direction)
    {
        auto world = ManagersProvider::Instance().GetWorld();
        auto assetsManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();

        auto bullet = world->CreateEntity();
        world->AddComponent<Bullet>(bullet, owner);
        world->AddComponent<Transform>(bullet, position, 0.f, glm::vec3(1.f, 1.f, 1.f));
        world->AddComponent<RigidBody>(bullet, direction);
        world->AddComponent<BoundingBox>(bullet, glm::vec3(4.f, 4.f, 0.f));
        world->AddComponent<SDLSprite>(bullet, assetsManager->GetAsset("bullet"), 4, 4, 0, 0, 4, 4);
        
    }
}
