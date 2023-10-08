#pragma once

#include "ECS/Systems/RenderSystem.h"

#include <glm/glm.hpp>

namespace shen
{
    class OpenGLSpriteRenderSystem
        : public RenderSystem
    {
    public:
        void Start() override;
        void Draw() override;

    private:
        glm::mat4 _projectionsMat;
    };
}
