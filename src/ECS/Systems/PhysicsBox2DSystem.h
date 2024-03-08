#pragma once

#include "System.h"
#include <box2d/box2d.h>
#include <memory>

namespace shen
{
    class PhysicsBox2DSystem
        : public System
    {
    public:
        void Start() override;
        void Update() override;
        void Stop() override;

    private:
        std::unique_ptr<b2World> _world;
    };
}
