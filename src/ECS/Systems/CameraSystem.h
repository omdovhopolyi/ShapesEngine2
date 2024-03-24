#pragma once

#include "System.h"
#include <glm/glm.hpp>

namespace shen
{
    class CameraSystem
        : public System
    {
    public:
        void Start() override;
        void Update() override;

    private:
        glm::vec2 _viewportSize;
    };
}
