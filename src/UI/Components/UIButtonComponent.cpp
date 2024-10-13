#include "UIButtonComponent.h"
#include "UI/UIWindow.h"
#include "UI/UINode.h"
#include "Utils/Math.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "Commands/CommandContext.h"
#include "Input/InputType.h"
#include "Utils/Assert.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace shen
{
    void ButtonSignal::Subscribe(ButtonSignalType type, const Callback& callback)
    {
        auto& list = _subscriptions[type];
        list.push_back(callback);
    }

    void ButtonSignal::Clear()
    {
        _subscriptions.clear();
    }

    void ButtonSignal::OnEvent(ButtonSignalType type)
    {
        if (auto it = _subscriptions.find(type); it != _subscriptions.end())
        {
            for (auto& callback : it->second)
            {
                callback();
            }
        }
    }

    void UIButtonComponent::Update(float dt)
    {
    }

    void UIButtonComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        target.draw(_current, transform);
    }

    void UIButtonComponent::SetSprite(ButtonSpriteType type, const sf::Sprite& sprite)
    {
        switch (type)
        {
        case ButtonSpriteType::Idle:
        {
            SetIdle(sprite);
            break;
        }
        case ButtonSpriteType::Hovered:
        {
            SetHovered(sprite);
            break;
        }
        case ButtonSpriteType::Pressed:
        {
            SetPressed(sprite);
            break;
        }
        default:
        {
            Assert(false, "[UIButtonComponent::SetSprite] Undefined sprite type");
        }
        }
    }

    void UIButtonComponent::SetIdle(const sf::Sprite& sprite)
    {
        _idle = sprite;
        _current = _idle;
    }

    sf::Sprite& UIButtonComponent::GetIdle()
    {
        return _idle;
    }

    void UIButtonComponent::SetPressed(const sf::Sprite& sprite)
    {
        _pressed = sprite;
    }

    sf::Sprite& UIButtonComponent::GetPressed()
    {
        return _pressed;
    }

    void UIButtonComponent::SetHovered(const sf::Sprite& sprite)
    {
        _hovered = sprite;
    }

    sf::Sprite& UIButtonComponent::GetHovered()
    {
        return _hovered;
    }

    bool UIButtonComponent::ProcessInput(const InputType& inputType, const CommandContext& context)
    {
        bool processed = false;

        switch (inputType.type)
        {
        case InputEventType::Up:
        {
            processed = HandleCursorRelease(inputType, context);
            break;
        }
        case InputEventType::Down:
        {
            processed = HandleCursorPress(inputType, context);
            break;
        }
        case InputEventType::MouseMove:
        {
            processed = HandleCursorMove(inputType, context);
            break;
        }
        }

        return processed;
    }

    bool UIButtonComponent::HandleCursorPress(const InputType& inputType, const CommandContext& context)
    {
        const bool isOverButton = IsCursorOverButton(inputType, context);
        const auto& spriteToSet = isOverButton ? _pressed : _idle;
        SetCurrentSprite(spriteToSet);
        _isPressed = isOverButton;

        if (_isPressed)
        {
            _signal.OnEvent(ButtonSignalType::Down);
        }
        
        return isOverButton;
    }

    bool UIButtonComponent::HandleCursorRelease(const InputType& inputType, const CommandContext& context)
    {
        const bool isOverButton = IsCursorOverButton(inputType, context);
        const auto& spriteToSet = isOverButton ? _hovered : _idle;
        SetCurrentSprite(spriteToSet);

        if (_isPressed)
        {
            _signal.OnEvent(ButtonSignalType::Up);
        }

        _isPressed = false;

        return isOverButton;
    }

    bool UIButtonComponent::HandleCursorMove(const InputType& inputType, const CommandContext& context)
    {
        const bool isOverButton = IsCursorOverButton(inputType, context);

        if (isOverButton)
        {
            if (IsPressed())
            {
                SetCurrentSprite(_pressed);
            }
            else
            {
                SetCurrentSprite(_hovered);
            }
        }
        else
        {
            SetCurrentSprite(_idle);
            SetPressed(false);
        }

        return isOverButton;
    }

    bool UIButtonComponent::IsCursorOverButton(const InputType& inputType, const CommandContext& context)
    {
        bool isOverButton = false;

        if (const auto screenPos = context.vars.GetVar<sf::Vector2i>("pos"))
        {
            auto window = _node->GetWindow();
            auto systems = window->GetSystemsManager();
            auto renderTargets = systems->GetSystem<SfmlRenderTargetsSystem>();
            if (auto uiTarget = renderTargets->GetRenderTexture(SfmlRenderTargetsSystem::UITargetId))
            {
                const auto worldPos = uiTarget->mapPixelToCoords(*screenPos);
                const auto& nodeTransform = _node->GetTransform();
                const auto spriteRect = nodeTransform.transformRect(_current.getLocalBounds());
                isOverButton = spriteRect.contains(worldPos);
            }
        }

        return isOverButton;
    }

    void UIButtonComponent::SetCurrentSprite(const sf::Sprite& sprite)
    {
        _current = sprite;
    }

    void UIButtonComponent::SetPressed(bool pressed)
    {
        _isPressed = pressed;
    }

    bool UIButtonComponent::IsPressed() const
    {
        return _isPressed;
    }
}
