#include "PlayerInputSystem.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include "Logger/Logger.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/InputCommandsCollection.h"
#include "ECS/Systems/ResourcesManagerHolderSystem.h"
#include "Commands/MoveCommands.h"
#include "Commands/FireCommand.h"
#include "Commands/RotateCommand.h"
#include "Resources/ResourcesManager.h"
#include "Resources/InputCommandsManager.h"
#include "Utils/Assert.h"

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

        return false;
    }

    bool operator == (const InputType& left, const InputType& right)
    {
        return (left.keyCode == right.keyCode &&
            left.mouseButton == right.mouseButton &&
            left.type == right.type &&
            left.alt == right.alt &&
            left.shift == right.shift &&
            left.ctrl == right.ctrl);
    }

    PlayerInputSystem::PlayerInputSystem()
        : UpdateSystem()
    {}

    void PlayerInputSystem::Start()
    {
        InitActionCallbacks();
        InitSubscriptions();
    }

    void PlayerInputSystem::Update()
    {
        std::vector<std::pair<Entity, const PlayerInput*>> entities;

        auto& world = _systems->GetWorld();
        world.Each<PlayerInput>([&](auto entity, const PlayerInput& input)
        {
            entities.push_back({ entity, &input });
        });

        for (auto& [entity, input] : entities)
        {
            for (auto& [command, context] : _toProcess)
            {
                if (command)
                {
                    command->Execute(entity, context);
                }
            }
        }

        _toProcess.clear();
    }

    void PlayerInputSystem::InitActionCallbacks()
    {
        LoadConfig();
    }

    void PlayerInputSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            InputType inputEvent;
            inputEvent.keyCode = event.code;
            inputEvent.type = event.type;
            inputEvent.alt = event.alt;
            inputEvent.shift = event.shift;
            inputEvent.ctrl = event.ctrl;

            if (auto it = _actions.find(inputEvent); it != _actions.end())
            {
                _toProcess.push_back({ it->second, {} });
            }
        });

        _subscriptions.Subscribe<MouseButtonEvent>([&](const MouseButtonEvent& event)
        {
            InputType inputEvent;
            inputEvent.mouseButton = event.button;
            inputEvent.type = event.type;
            inputEvent.alt = event.alt;
            inputEvent.shift = event.shift;
            inputEvent.ctrl = event.ctrl;

            if (auto it = _actions.find(inputEvent); it != _actions.end())
            {
                _toProcess.push_back({ it->second, {} });
            }
        });

        _subscriptions.Subscribe<MouseMoveEvent>([&](const MouseMoveEvent& event)
        {
            InputType inputEvent;
            inputEvent.type = InputEventType::MouseMove;
            inputEvent.alt = event.alt;
            inputEvent.shift = event.shift;
            inputEvent.ctrl = event.ctrl;

            CommandContext context;
            context.x = event.x;
            context.y = event.y;

            if (auto it = _actions.find(inputEvent); it != _actions.end())
            {
                _toProcess.push_back({ it->second, context });
            }
        });

        _subscriptions.Subscribe<MouseWheelEvent>([&](const MouseWheelEvent& event)
        {
            InputType inputEvent;
            inputEvent.type = InputEventType::Scroll;
            inputEvent.alt = event.alt;
            inputEvent.shift = event.shift;
            inputEvent.ctrl = event.ctrl;

            CommandContext context;
            context.y = event.scroll;

            if (auto it = _actions.find(inputEvent); it != _actions.end())
            {
                _toProcess.push_back({ it->second, context });
            }
        });
    }

    void PlayerInputSystem::LoadConfig()
    {
        auto inputCommandsCollection = _systems->GetSystem<InputCommandsCollection>();

        /*auto resourcesManagerHolder = _systems->GetSystem<ResourcesManagerHolderSystem>();
        auto resourcesManager = resourcesManagerHolder->GetResourcesManager();
        auto commandsManager = resourcesManager->GetOrCreateAssetsManager<InputCommandsManager>();*/
        
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile("../assets/configs/input.xml");
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, "[PlayerInputSystem::LoadConfig] Can not read 'input.xml");
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto element = elements->FirstChildElement("item");
            while (element)
            {
                InputType inputType;

                if (const auto keyAttr = element->FindAttribute("key"))
                {
                    inputType.keyCode = static_cast<int>(*keyAttr->Value());
                }

                if (const auto mouseBtnAttr = element->FindAttribute("mouseBtn"))
                {
                    inputType.mouseButton = MouseButtonEnum.FromString(mouseBtnAttr->Value());
                }

                if (const auto inputEventTypeAttr = element->FindAttribute("inputEventType"))
                {
                    inputType.type = InputEventTypeEnum.FromString(inputEventTypeAttr->Value());
                }

                if (const auto modeAttr = element->FindAttribute("alt"))
                {
                    inputType.alt = modeAttr->BoolValue();
                }

                if (const auto modeAttr = element->FindAttribute("shift"))
                {
                    inputType.shift = modeAttr->BoolValue();
                }

                if (const auto modeAttr = element->FindAttribute("ctrl"))
                {
                    inputType.ctrl = modeAttr->BoolValue();
                }

                if (const auto commandAttr = element->FindAttribute("command"))
                {
                    const auto commandId = commandAttr->Value();
                    auto command = inputCommandsCollection->GetCommandById(commandId);

                    _actions[inputType] = command;
                }
                
                element = element->NextSiblingElement();
            }
        }
    }
}
