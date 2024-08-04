#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class CameraSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(CameraSystem)

    public:
        void Update() override;
    };
}
