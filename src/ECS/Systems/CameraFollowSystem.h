#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class CameraFollowSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
