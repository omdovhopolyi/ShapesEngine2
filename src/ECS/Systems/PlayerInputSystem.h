#pragma once

#include "System.h"
#include "Messenger/SubscriptionsContainer.h"
#include "Utils/Types.h"
#include "Enums/Direction.h"

#include <glm/glm.hpp>

namespace shen
{
    class PlayerInputSystem
        : public System
    {
    public:
        using ActionCallback = std::function<void()>;
        using KeyCode = int;

        PlayerInputSystem();

        void Start() override;
        void Update() override;

    private:
        void InitActionsMapping();
        void InitActionCallbacks();
        void InitSubscriptions();

        void RunActions();
        void UpdateObjects();

    private:
        SubcriptionsContainer _subscriptions;
        std::vector<KeyCode> _toProcess;

        glm::vec3 _direction = glm::vec3(0.f);

        std::map<KeyCode, ActionType> _actionsMapping;
        std::map<ActionType, ActionCallback> _actionCallbacks;
    };
}
