#include "PlayerInputSystem.h"

#include "Game/ManagersProvider.h"
#include "Resources/SDLTexturesManager.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include "Logger/Logger.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "Commands/MoveCommands.h"
#include "Commands/FireCommand.h"
#include "Commands/RotateCommand.h"

namespace shen
{
    bool operator < (const InputType& left, const InputType& right)
    {
        if (left.keyCode != right.keyCode)
        {
            return left.keyCode < right.keyCode;
        }
        if (left.mouseButton != right.mouseButton)
        {
            return left.mouseButton < right.mouseButton;
        }
        if (left.type != right.type)
        {
            return left.type < right.type;
        }
        if (left.mode != right.mode)
        {
            return left.mode < right.mode;
        }

        return false;
    }

    bool operator == (const InputType& left, const InputType& right)
    {
        return (left.keyCode == right.keyCode &&
            left.mouseButton == right.mouseButton &&
            left.type == right.type &&
            left.mode == right.mode);
    }

    PlayerInputSystem::PlayerInputSystem()
        : System()
    {}

    void PlayerInputSystem::Start()
    {
        InitActionCallbacks();
        InitSubscriptions();
    }

    void PlayerInputSystem::Update()
    {
        std::vector<Entity> entities;

        auto world = ManagersProvider::Instance().GetWorld();
        world->Each<PlayerInput>(
            [&](auto entity, const PlayerInput&)
        {
            entities.push_back(entity);
        });

        for (auto& entity : entities)
        {
            for (auto& [command, context] : _toProcess)
            {
                command->Execute(entity, context);
            }
        }

        _toProcess.clear();
    }

    void PlayerInputSystem::InitActionCallbacks()
    {
        // TODO config

        _actions[{ 
            static_cast<int>('w'),
            MouseButton::None,
            InputEventType::Hold,
            KeyMode::None
        }] = std::make_shared<MoveUpCommand>();

        _actions[{ 
            static_cast<int>('d'),
            MouseButton::None,
            InputEventType::Hold,
            KeyMode::None
        }] = std::make_shared<MoveRightCommand>();

        _actions[{ 
            static_cast<int>('s'),
            MouseButton::None,
            InputEventType::Hold,
            KeyMode::None
        }] = std::make_shared<MoveDownCommand>();

        _actions[{ 
            static_cast<int>('a'),
            MouseButton::None,
            InputEventType::Hold,
            KeyMode::None
        }] = std::make_shared<MoveLeftCommand>();

        /*_actions[{ 
            static_cast<int>(' '),
            MouseButton::None,
            InputEventType::Down,
            KeyMode::None
        }] = std::make_shared<FireCommand>();*/

        _actions[{ 
            -1,
            MouseButton::None,
            InputEventType::MouseMove,
            KeyMode::None
        }] = std::make_shared<RotateCommand>();
    }

    void PlayerInputSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            InputType inputEvent;
            inputEvent.keyCode = event.code;
            inputEvent.type = event.type;
            inputEvent.mode = event.mode;

            if (auto it = _actions.find(inputEvent); it != _actions.end())
            {
                _toProcess.push_back({ it->second.get(), {} });
            }
        });

        _subscriptions.Subscribe<MouseButtonEvent>([&](const MouseButtonEvent& event)
        {
            InputType inputEvent;
            inputEvent.mouseButton = event.button;
            inputEvent.type = event.type;
            inputEvent.mode = event.mode;

            if (auto it = _actions.find(inputEvent); it != _actions.end())
            {
                _toProcess.push_back({ it->second.get(), {} });
            }
        });

        _subscriptions.Subscribe<MouseMoveEvent>([&](const MouseMoveEvent& event)
        {
            InputType inputEvent;
            inputEvent.type = InputEventType::MouseMove;

            CommandContext context;
            context.x = event.x;
            context.y = event.y;

            if (auto it = _actions.find(inputEvent); it != _actions.end())
            {
                _toProcess.push_back({ it->second.get(), context });
            }
        });
    }
}
