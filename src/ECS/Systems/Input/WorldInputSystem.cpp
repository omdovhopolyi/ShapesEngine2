#include "WorldInputSystem.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include "Logger/Logger.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Input/InputCommandsCollection.h"
#include "ECS/Systems/Sfml/SfmlInputSystem.h"
#include "Utils/Assert.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(WorldInputSystem)

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
        return (left.keyCode == right.keyCode && left.keyCode > -1 &&
            left.mouseButton == right.mouseButton &&
            left.type == right.type &&
            left.alt == right.alt &&
            left.shift == right.shift &&
            left.ctrl == right.ctrl);
    }

    void WorldInputSystem::Start()
    {
        LoadConfig();
    }

    void WorldInputSystem::Update()
    {
        if (_toProcess.empty())
        {
            return;
        }

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
                    const bool canExecute = input->commandTypes.contains(command->GetType());
                    if (canExecute)
                    {
                        context.entity = entity;
                        context.systems = _systems;

                        command->Execute(context);
                    }
                }
            }
        }

        _toProcess.clear();
    }

    bool WorldInputSystem::OnKeyEvent(const KeyEvent& event)
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
            return true;
        }

        return false;
    }

    bool WorldInputSystem::OnMouseButtonEvent(const MouseButtonEvent& event)
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
            return true;
        }

        return false;
    }

    bool WorldInputSystem::OnMouseMoveEvent(const MouseMoveEvent& event)
    {
        InputType inputEvent;
        inputEvent.mouseButton = event.button;
        inputEvent.type = InputEventType::MouseMove;
        inputEvent.alt = event.alt;
        inputEvent.shift = event.shift;
        inputEvent.ctrl = event.ctrl;

        CommandContext context;
        context.vars.SetVar("pos", sf::Vector2i(event.x, event.y));
        context.vars.SetVar("delta", sf::Vector2i(event.dx, event.dy));

        if (auto it = _actions.find(inputEvent); it != _actions.end())
        {
            _toProcess.push_back({ it->second, context });
            return true;
        }

        return false;
    }

    bool WorldInputSystem::OnMouseWheelEvent(const MouseWheelEvent& event)
    {
        InputType inputEvent;
        inputEvent.type = InputEventType::Scroll;
        inputEvent.alt = event.alt;
        inputEvent.shift = event.shift;
        inputEvent.ctrl = event.ctrl;

        CommandContext context;
        context.vars.SetVar("var", event.scroll);

        if (auto it = _actions.find(inputEvent); it != _actions.end())
        {
            _toProcess.push_back({ it->second, context });
            return true;
        }

        return false;
    }

    void WorldInputSystem::LoadConfig()
    {
        auto inputCommandsCollection = _systems->GetSystem<InputCommandsCollection>();
        auto sfmlInputSystem = _systems->GetSystem<SfmlInputSystem>();

        auto serialization = Serialization{ _systems, "../assets/configs/input.xml" };
        serialization.SetupElement("items");
        serialization.ForAllChildElements("item", [&](const Serialization& element)
        {
            InputType inputType;
            const bool silent = true;

            inputType.keyCode = static_cast<int>(sfmlInputSystem->GetKeyByChar(element.GetStr("key"), silent));
            inputType.mouseButton = MouseButtonEnum.FromString(element.GetStr("mouseBtn"));
            inputType.type = InputEventTypeEnum.FromString(element.GetStr("inputEventType"));
            inputType.alt = element.GetBool("alt");
            inputType.shift = element.GetBool("shift");
            inputType.ctrl = element.GetBool("ctrl");
            
            if (const auto commandId = element.GetStr("command"); !commandId.empty())
            {
                auto command = inputCommandsCollection->GetCommandById(commandId);
                _actions[inputType] = command;
            }
        });
    }
}
