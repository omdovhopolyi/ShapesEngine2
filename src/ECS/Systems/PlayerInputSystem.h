#pragma once

#include "System.h"
#include "Messenger/SubscriptionsContainer.h"
#include "Utils/Types.h"
#include "Enums/Direction.h"

#include "Commands/Command.h"

#include <memory>

namespace shen
{
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
        using KeyCode = int;
        using CommandsMap = std::map<KeyCode, std::shared_ptr<Command>>;
        using WeakCommands = std::vector<std::weak_ptr<Command>>;

        PlayerInputSystem();

        void Start() override;
        void Update() override;

    private:
        void InitActionCallbacks();
        void InitSubscriptions();

        void ProcessCommands(Entity entity, const WeakCommands& commands);

        WeakCommands ProcessEvents(std::vector<KeyCode>& toProcess, CommandsMap& callbacks);

    private:
        SubcriptionsContainer _subscriptions;

        std::vector<KeyCode> _toProcessOnDown;
        std::vector<KeyCode> _toProcessOnHold;
        std::vector<KeyCode> _toProcessOnUp;

        CommandsMap _actionsOnDown;
        CommandsMap _actionsOnHold;
        CommandsMap _actionsOnUp;
    };
}
