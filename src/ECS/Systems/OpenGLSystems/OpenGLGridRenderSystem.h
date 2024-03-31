#pragma once

#include "ECS/Systems/RenderSystem.h"
#include "Messenger/SubscriptionsContainer.h"

#include <glm/glm.hpp>

namespace shen
{
    class OpenGLGridRenderSystem
        : public RenderSystem
    {
    public:
        void Start() override;
        void Draw() override;

    private:
        void InitSubscriptions();
        void InitBuffers();

    private:
        unsigned int VBO = 0;
        unsigned int UV = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;

        SubcriptionsContainer _subscriptions;
    };
}
