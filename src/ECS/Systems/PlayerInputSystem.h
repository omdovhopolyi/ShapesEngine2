#pragma once

#include "System.h"
#include "Messenger/SubscriptionsContainer.h"
#include "Utils/Types.h"
#include "Enums/Direction.h"

#include <glm/glm.hpp>

namespace shen
{
    /*class InputCommand
    {
    public:
        InputCommand();
        InputCommand(KeyEventType type);

    protected:
        KeyEventType _type = KeyEventType::Undefined;
    };*/

    /*struct ActionData
    {
        std::string key;
        std::string type;
        std::string actionId;
    };*/

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
        //void InitActionsMapping();
        void InitActionCallbacks();
        void InitSubscriptions();

        void UpdateObjects();

        void ProcessEvents(std::vector<KeyCode>& toProcess, std::map<KeyCode, ActionCallback>& callbacks);

    private:
        SubcriptionsContainer _subscriptions;

        std::vector<KeyCode> _toProcessOnDown;
        std::vector<KeyCode> _toProcessOnHold;
        std::vector<KeyCode> _toProcessOnUp;

        glm::vec3 _direction = glm::vec3(0.f); // move

        std::map<KeyCode, ActionCallback> _actionsOnDown;
        std::map<KeyCode, ActionCallback> _actionsOnHold;
        std::map<KeyCode, ActionCallback> _actionsOnUp;
    };
}
