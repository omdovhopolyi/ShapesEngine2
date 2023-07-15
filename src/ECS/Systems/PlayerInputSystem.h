#pragma once

#include "System.h"
#include "Messenger/SubscriptionsContainer.h"

#include <glm/glm.hpp>

namespace shen
{
    enum class ActionType
    {
        Forward, // Up
        Right,
        Backward, // Down
        Left,
        Fire
    };

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
        SubcriptionsContainer _subscriptions;
        std::vector<KeyCode> _toProcess;

        glm::vec3 _direction = glm::vec3(0.f);

        std::map<KeyCode, ActionType> _actionsMapping;
        std::map<ActionType, ActionCallback> _actionCallbacks;
    };
}
