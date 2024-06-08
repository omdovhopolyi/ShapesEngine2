#pragma once

#include "BaseSystems/UpdateSystem.h"

namespace shen
{
    class CameraSystem
        : public UpdateSystem
    {
    public:
        void Update() override;
    };
}
