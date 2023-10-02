#pragma once

#include "ECS/Systems/RenderSystem.h"

namespace shen
{
    class OpenGLSpriteRenderSystem
        : public RenderSystem
    {
    public:
        void Start() override;
        void Draw() override;
    };
}
