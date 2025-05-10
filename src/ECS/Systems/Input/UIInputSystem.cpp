#include "UIInputSystem.h"
#include "Input/InputType.h"
#include "Commands/CommandContext.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(UIInputSystem)

    void UIInputSystem::Start()
    {
        _windows = _systems->GetSystem<WindowsManager>();
    }

    void UIInputSystem::Update()
    {

    }

    bool UIInputSystem::OnKeyEvent(const KeyEvent& event)
    {
        return false;
    }

    bool UIInputSystem::OnMouseButtonEvent(const MouseButtonEvent& event)
    {
        if (_windows)
        {
            InputType inputEvent;
            inputEvent.mouseButton = event.button;
            inputEvent.type = event.type;
            inputEvent.alt = event.alt;
            inputEvent.shift = event.shift;
            inputEvent.ctrl = event.ctrl;

            CommandContext context;
            context.vars.SetVar("pos", sf::Vector2i(event.x, event.y));

            return _windows->ProcessInput(inputEvent, context);
        }

        return false;
    }

    bool UIInputSystem::OnMouseMoveEvent(const MouseMoveEvent& event)
    {
        if (_windows)
        {
            InputType inputEvent;
            inputEvent.type = InputEventType::MouseMove;
            inputEvent.alt = event.alt;
            inputEvent.shift = event.shift;
            inputEvent.ctrl = event.ctrl;

            CommandContext context;
            context.vars.SetVar("pos", sf::Vector2i(event.x, event.y));

            return _windows->ProcessInput(inputEvent, context);
        }

        return false;
    }

    bool UIInputSystem::OnMouseWheelEvent(const MouseWheelEvent& event)
    {
        return false;
    }
}
