#pragma once

#include "BaseSystems/UpdateSystem.h"
#include "Messenger/SubscriptionsContainer.h"
#include "Messenger/Events/Common.h"
#include "Utils/Types.h"
#include "Enums/Direction.h"
#include "Enums/MouseButtonEnum.h"
#include "Enums/InputEventTypeEnum.h"
#include "Enums/KeyModeEnum.h"

#include "Commands/Command.h"

#include <memory>

namespace shen
{
    struct InputType
    {
        int keyCode = -1;
        MouseButton mouseButton = MouseButton::None;
        InputEventType type = InputEventType::Undefined;
        KeyMode mode = KeyMode::None;

        friend bool operator < (const InputType& left, const InputType& right);
        friend bool operator == (const InputType& left, const InputType& right);
    };

    class PlayerInputSystem
        : public UpdateSystem
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
        void LoadConfig();

    protected:
        SubcriptionsContainer _subscriptions;

        std::map<InputType, std::shared_ptr<Command>> _actions;
        std::vector<std::pair<Command*, CommandContext>> _toProcess;
    };
}
