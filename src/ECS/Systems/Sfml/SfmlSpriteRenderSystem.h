#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"
#include "Messenger/SubscriptionsContainer.h"

namespace shen
{
    class SfmlSpriteRenderSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(SfmlSpriteRenderSystem)

    public:
        void Init(SystemsManager* systems) override;
        void Start() override;
        void Draw() override;

    private:
        void InitSubscriptions();

    private:
        SubcriptionsContainer _subscriptions;
    };
}
