#pragma once

#include "System.h"
#include "Messenger/SubscriptionsContainer.h"
#include "Messenger/Events/Common.h"
#include "Utils/Types.h"
#include "Enums/Direction.h"

#include "Commands/Command.h"

#include <memory>

namespace shen
{
    struct InputData
    {
        int keyCode = -1;
        MouseButton mouseButton = MouseButton::None;
        InputEventType type = InputEventType::Undefined;
        KeyMode mode = KeyMode::None;
        int x = 0;
        int y = 0;

        friend bool operator < (const InputData& left, const InputData& right);
        friend bool operator == (const InputData& left, const InputData& right);
    };

    class PlayerInputSystem
        : public System
    {
    public:
        using InputCode = int;
        using CommandsMap = std::map<InputCode, std::shared_ptr<Command>>;
        using WeakCommands = std::vector<std::weak_ptr<Command>>;

        PlayerInputSystem();

        void Start() override;
        void Update() override;

    protected:
        virtual void InitActionCallbacks();
        void InitSubscriptions();
    protected:
        SubcriptionsContainer _subscriptions;

        std::map<InputData, std::shared_ptr<Command>> _actions;
        std::vector<Command*> _toProcess;
    };
}
