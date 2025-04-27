#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class CameraFollowSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(CameraFollowSystem)

    public:
        void Update() override;
    };
}
