#pragma once

#include "ECS/Systems/System.h"
#include "Messenger/SubscriptionsContainer.h"

namespace shen
{
    class EditorSystem
        : public System
    {
    public:
        void Start() override;
        void Update() override;
        void Stop() override;

        bool IsActive() const { return _isActive; }

    public:
        void InitSubscriptions();
        void InitImgui();
        void DeinitImgui();

    private:
        bool _isInited = false;
        bool _isActive = false;
        SubcriptionsContainer _subscriptions;

        bool _demo = false;
        bool _test = false;
    };
}
