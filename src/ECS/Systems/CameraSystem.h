#pragma once

#include "BaseSystems/UpdateSystem.h"
#include <glm/glm.hpp>

namespace shen
{
    class CameraSystem
        : public UpdateSystem
    {
    public:
        void Start() override;
        void Update() override;

    private:
        glm::vec2 _viewportSize;
    };
}
