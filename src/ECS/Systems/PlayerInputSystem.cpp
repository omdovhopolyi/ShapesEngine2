#include "PlayerInputSystem.h"

#include "Game/ManagersProvider.h"
#include "Resources/SDLTexturesManager.h"
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
        InitActionCallbacks();
        InitSubscriptions();
    }

    void PlayerInputSystem::Update()
    {
        ProcessEvents(_toProcessOnDown, _actionsOnDown);
        ProcessEvents(_toProcessOnHold, _actionsOnHold);
        ProcessEvents(_toProcessOnUp, _actionsOnUp);

        UpdateObjects();
    }

    void PlayerInputSystem::InitActionCallbacks()
    {
        auto moveForward = [this]()
        {
            _direction += glm::vec3(0.f, -1.f, 0.f);
        };

        auto moveRight = [this]()
        {
            _direction += glm::vec3(1.f, 0.f, 0.f);
        };

        auto moveBack = [this]()
        {
            _direction += glm::vec3(0.f, 1.f, 0.f);
        };

        auto moveLeft = [this]()
        {
            _direction += glm::vec3(-1.f, 0.f, 0.f);
        };

        auto fire = [this]()
        {
            auto world = ManagersProvider::Instance().GetWorld();
            auto assetsManager = ManagersProvider::Instance().GetOrCreateAssetsManager<SDLTexturesManager>();

            Entity playerEntity;
            glm::vec3 position{};

            world->Each<PlayerInput, Transform>(
                [&](auto entity, const PlayerInput& player, const Transform& transform)
            {
                playerEntity = entity;
                position = transform.position;
            });

            if (world->IsValid(playerEntity))
            {
                auto bullet = world->CreateEntity();
                world->AddComponent<Bullet>(bullet);
                world->AddComponent<Transform>(bullet, position, 0.f, glm::vec3(1.f, 1.f, 1.f));
                world->AddComponent<RigidBody>(bullet, glm::vec3(200.f, 0.f, 0.f));
                world->AddComponent<SDLSprite>(bullet, assetsManager->GetAsset("bullet"), 4, 4, 0, 0, 4, 4);
            }
        };

        _actionsOnDown[static_cast<KeyCode>('w')] = moveForward;
        _actionsOnDown[static_cast<KeyCode>('d')] = moveRight;
        _actionsOnDown[static_cast<KeyCode>('s')] = moveBack;
        _actionsOnDown[static_cast<KeyCode>('a')] = moveLeft;
        _actionsOnDown[static_cast<KeyCode>(' ')] = fire;
        
        _actionsOnHold[static_cast<KeyCode>('w')] = moveForward;
        _actionsOnHold[static_cast<KeyCode>('d')] = moveRight;
        _actionsOnHold[static_cast<KeyCode>('s')] = moveBack;
        _actionsOnHold[static_cast<KeyCode>('a')] = moveLeft;
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

    void PlayerInputSystem::ProcessEvents(std::vector<KeyCode>& toProcess, std::map<KeyCode, ActionCallback>& callbacks)
    {
        for (const auto& code : toProcess)
        {
            auto it = callbacks.find(code);
            if (it != callbacks.end())
            {
                it->second();
            }
        }

        toProcess.clear();
    }
}
