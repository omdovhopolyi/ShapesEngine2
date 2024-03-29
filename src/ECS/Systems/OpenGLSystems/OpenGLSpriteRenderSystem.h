#pragma once

#include "ECS/Systems/RenderSystem.h"
#include "Messenger/SubscriptionsContainer.h"

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
        void InitSubscriptions();
        void InitBuffers();;

    private:
        glm::mat4 _projectionsMat;

        SubcriptionsContainer _subscriptions;
    };
}
