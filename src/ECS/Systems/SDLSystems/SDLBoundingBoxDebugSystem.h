#pragma once

#include "SDLRenderSystem.h"
#include "Messenger/SubscriptionsContainer.h"

namespace shen
{
    class SDLBoundingBoxDebugSystem
        : public SDLRenderSystem
    {
    public:
        void Start() override;
        void Draw() override;

        bool IsActivated() const { return _isActivated; }

    protected:
        void Subscribe();

    private:
        bool _isActivated = false;
        SubcriptionsContainer _subscriptions;
    };
}
