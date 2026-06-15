#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"

namespace shen
{
    class GLEWSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(GLEWSystem)

    public:
        void Init(SystemsManager* systems) override;
        void Start() override;
        void Draw() override;
    };
}
