#include "PlayerInputSystem.h"

#include "Game/ManagersProvider.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include "Logger/Logger.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/SDLComponents.h"
#include "Utils/Math.h"

#include <glm/gtx/vector_angle.hpp>

namespace shen
{
    PlayerInputSystem::PlayerInputSystem()
        : System()
    {
    }

    void PlayerInputSystem::Start()
    {
        InitActionsMapping();
        InitActionCallbacks();
        InitSubscriptions();
    }

    void PlayerInputSystem::Update()
    {
        RunActions();
        UpdateObjects();
    }

    void PlayerInputSystem::InitActionsMapping()
    {
        _actionsMapping[static_cast<KeyCode>('w')] = ActionType::Forward;
        _actionsMapping[static_cast<KeyCode>('d')] = ActionType::Right;
        _actionsMapping[static_cast<KeyCode>('s')] = ActionType::Backward;
        _actionsMapping[static_cast<KeyCode>('a')] = ActionType::Left;
        _actionsMapping[static_cast<KeyCode>(' ')] = ActionType::Fire;
    }

    void PlayerInputSystem::InitActionCallbacks()
    {
        _actionCallbacks[ActionType::Forward] = [this]()
        {
            _direction += glm::vec3(0.f, -1.f, 0.f);
        };

        _actionCallbacks[ActionType::Right] = [this]()
        {
            _direction += glm::vec3(1.f, 0.f, 0.f);
        };

        _actionCallbacks[ActionType::Backward] = [this]()
        {
            _direction += glm::vec3(0.f, 1.f, 0.f);
        };

        _actionCallbacks[ActionType::Left] = [this]()
        {
            _direction += glm::vec3(-1.f, 0.f, 0.f);
        };

        _actionCallbacks[ActionType::Fire] = [this]()
        {
            Logger::Log("Fire");
        };
    }

    void PlayerInputSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            if (event.type == KeyEventType::Down ||
                event.type == KeyEventType::Hold)
            {
                _toProcess.push_back(event.code);   
            }
        });
    }

    void PlayerInputSystem::RunActions()
    {
        for (const auto& code : _toProcess)
        {
            auto it = _actionsMapping.find(code);
            if (it != _actionsMapping.end())
            {
                auto actionIt = _actionCallbacks.find(it->second);
                if (actionIt != _actionCallbacks.end())
                {
                    actionIt->second();
                }
            }
        }

        _toProcess.clear();
    }

    void PlayerInputSystem::UpdateObjects()
    {
        glm::vec3 velocity{};
        const bool hasDirection = SquareLength(_direction) > 0.f;

        if (hasDirection)
        {
            _direction = glm::normalize(_direction);
        }

        auto world = ManagersProvider::Instance().GetWorld();
        world->Each<PlayerInput, RigidBody>(
            [&](auto entity, const PlayerInput& player, RigidBody& rigidBody)
        {
            rigidBody.velocity = _direction * player.speed;
        });

        _direction = glm::vec3{};
    }
}
