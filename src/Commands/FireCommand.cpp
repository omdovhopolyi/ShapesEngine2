#include "FireCommand.h"

#include "Game/ManagersProvider.h"
#include "Game/WeaponManager.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void FireCommand::Execute(const Entity& entity) const
    {
        auto world = ManagersProvider::Instance().GetWorld();
        auto weapon = ManagersProvider::Instance().GetWeaponManager();
        
        if (auto transform = world->GetComponent<Transform>(entity))
        {
            auto position = transform->position;

            if (auto bb = world->GetComponent<BoundingBox>(entity))
            {
                position += bb->offset;
                position += bb->size / 2.f;
            }

            weapon->FireBullet(position, glm::vec3(1.f, 0.f, 0.f));
        }
        else
        {
            // assert
        }
    }
}
