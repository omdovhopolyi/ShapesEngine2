#include "PlayerInputSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/WorldInputSystem.h"
#include "ECS/Systems/UIInputSystem.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(PlayerInputSystem)

    void PlayerInputSystem::Init(SystemsManager* systems)
    {
        UpdateSystem::Init(systems);
        InitSubscriptions();
    }

    void PlayerInputSystem::Start()
    {
        SetupInputSystems();
    }

    void PlayerInputSystem::Update()
    {

    }

    void PlayerInputSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([&](const KeyEvent& event)
        {
            for (auto system : _inputSystems)
            {
                const bool isProcessed = system->OnKeyEvent(event);
                if (isProcessed)
                {
                    break;
                }
            }
        });

        _subscriptions.Subscribe<MouseButtonEvent>([&](const MouseButtonEvent& event)
        {
            for (auto system : _inputSystems)
            {
                const bool isProcessed = system->OnMouseButtonEvent(event);
                if (isProcessed)
                {
                    break;
                }
            }
        });

        _subscriptions.Subscribe<MouseMoveEvent>([&](const MouseMoveEvent& event)
        {
            for (auto system : _inputSystems)
            {
                const bool isProcessed = system->OnMouseMoveEvent(event);
                if (isProcessed)
                {
                    break;
                }
            }
        });

        _subscriptions.Subscribe<MouseWheelEvent>([&](const MouseWheelEvent& event)
        {
            for (auto system : _inputSystems)
            {
                const bool isProcessed = system->OnMouseWheelEvent(event);
                if (isProcessed)
                {
                    break;
                }
            }
        });
    }

    void PlayerInputSystem::SetupInputSystems()
    {
        _inputSystems.clear();
        _inputSystems.push_back(_systems->GetSystem<UIInputSystem>());
        _inputSystems.push_back(_systems->GetSystem<WorldInputSystem>());
    }
}
