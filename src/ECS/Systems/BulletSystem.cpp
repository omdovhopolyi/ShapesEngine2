#include "BulletSystem.h"

#include "Game/ManagersProvider.h"
#include "Game/Time.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

namespace shen
{
    void BulletSystem::Update()
    {
        /*auto world = ManagersProvider::Instance().GetWorld();
        auto dt = ManagersProvider::Instance().GetTime();

        world->Each<Bullet>([&](auto entity, Bullet& bullet)
        {
            bullet.lifeTime -= dt->Dt();
            if (bullet.lifeTime <= 0.f)
            {
                world->AddComponent<Destroy>(entity);
            }
        });*/
    }
}
