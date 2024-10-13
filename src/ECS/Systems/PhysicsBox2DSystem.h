#pragma once

#include "BaseSystems/UpdateSystem.h"
#include "Physics/CollisionListener.h"
#include <box2d/box2d.h>
#include <memory>

namespace shen
{
    class PhysicsBox2DSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(PhysicsBox2DSystem)

    public:
        void Start() override;
        void Update() override;
        void Stop() override;

        void SetupDefaultCollisionListener();
        void SetCollisionListener(std::unique_ptr<CollisionListener>& listener);

        bool InitWorld();
        void InitRigidBodies();

    private:
        void UpdatePhysics();

    private:
        std::unique_ptr<b2World> _world;
        std::unique_ptr<CollisionListener> _collisionListener;

        int32 _velocityIterations = 6;
        int32 _positionIterations = 2;
    };
}
