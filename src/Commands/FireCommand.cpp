#include "FireCommand.h"

#include "Game/ManagersProvider.h"
#include "Game/WeaponManager.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "Utils/Types.h"

#include <glm/glm.hpp>

namespace shen
{
    void FireCommand::Execute(const Entity& entity, const CommandContext&) const
    {
        //auto world = ManagersProvider::Instance().GetWorld();
        //auto weapon = ManagersProvider::Instance().GetWeaponManager();
        //
        //if (auto transform = world->GetComponent<Transform>(entity))
        //{
        //    auto position = transform->position;

        //    if (auto bb = world->GetComponent<BoundingBox>(entity))
        //    {
        //        position += bb->offset;
        //        position += bb->size / 2.f;
        //    }

        //    if (auto direction = world->GetComponent<Direction>(entity))
        //    {
        //        const auto bulletVelocity =  glm::normalize(direction->vec) * _bulletSpeed;
        //        weapon->FireBullet(entity, position, bulletVelocity);
        //    }
        //}
        //else
        //{
        //    // assert
        //}
    }
}
