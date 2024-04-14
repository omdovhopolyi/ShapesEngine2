#pragma once

#include "BaseSystems/UpdateSystem.h"
#include "Game/CollisionListener.h"
#include <box2d/box2d.h>
#include <memory>

namespace shen
{
    class PhysicsBox2DSystem
        : public UpdateSystem
    {
    public:
        void Start() override;
        void Update() override;
        void Stop() override;

    private:
        std::unique_ptr<b2World> _world;
        std::unique_ptr<CollisionListener> _collisionListener;
    };
}
