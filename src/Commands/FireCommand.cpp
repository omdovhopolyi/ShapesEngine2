#include "FireCommand.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "Utils/Types.h"

namespace shen
{
    void FireCommand::Execute(const CommandContext&) const
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
