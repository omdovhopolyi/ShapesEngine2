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

namespace shen
{
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
        auto commandsOnDown = ProcessEvents(_toProcessOnDown, _actionsOnDown);
        auto commandsOnHold = ProcessEvents(_toProcessOnHold, _actionsOnHold);
        auto commandsOnUp = ProcessEvents(_toProcessOnUp, _actionsOnUp);

        std::vector<Entity> entities;

        auto world = ManagersProvider::Instance().GetWorld();
        world->Each<PlayerInput>(
            [&](auto entity, const PlayerInput&)
        {
            entities.push_back(entity);
        });

        for (auto& entity : entities)
        {
            ProcessCommands(entity, commandsOnDown);
            ProcessCommands(entity, commandsOnHold);
            ProcessCommands(entity, commandsOnUp);
        }
    }

    void PlayerInputSystem::InitActionCallbacks()
    {
        _actionsOnDown[static_cast<KeyCode>('w')] = std::make_shared<MoveUpCommand>();
        _actionsOnDown[static_cast<KeyCode>('d')] = std::make_shared<MoveRightCommand>();
        _actionsOnDown[static_cast<KeyCode>('s')] = std::make_shared<MoveDownCommand>();
        _actionsOnDown[static_cast<KeyCode>('a')] = std::make_shared<MoveLeftCommand>();
        _actionsOnDown[static_cast<KeyCode>(' ')] = std::make_shared<FireCommand>();

        _actionsOnHold[static_cast<KeyCode>('w')] = std::make_shared<MoveUpCommand>();
        _actionsOnHold[static_cast<KeyCode>('d')] = std::make_shared<MoveRightCommand>();
        _actionsOnHold[static_cast<KeyCode>('s')] = std::make_shared<MoveDownCommand>();
        _actionsOnHold[static_cast<KeyCode>('a')] = std::make_shared<MoveLeftCommand>();
    }

    void PlayerInputSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            if (event.type == KeyEventType::Down)
            {
                _toProcessOnDown.push_back(event.code);
            }

            if (event.type == KeyEventType::Hold)
            {
                _toProcessOnHold.push_back(event.code);   
            }

            if (event.type == KeyEventType::Up)
            {
                _toProcessOnUp.push_back(event.code);
            }
        });
    }

    void PlayerInputSystem::ProcessCommands(Entity entity, const PlayerInputSystem::WeakCommands& commands)
    {
        for (const auto& commandPtr : commands)
        {
            if (auto command = commandPtr.lock())
            {
                command->Execute(entity);
            }
        }
    }

    PlayerInputSystem::WeakCommands PlayerInputSystem::ProcessEvents(std::vector<KeyCode>& toProcess, PlayerInputSystem::CommandsMap& callbacks)
    {
        PlayerInputSystem::WeakCommands commands;

        for (const auto& code : toProcess)
        {
            auto it = callbacks.find(code);
            if (it != callbacks.end())
            {
                commands.push_back(it->second);
            }
        }

        toProcess.clear();

        return commands;
    }
}
