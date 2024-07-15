#include "UIButtonComponent.h"
#include "UI/UIWindow.h"
#include "UI/UINode.h"
#include "Utils/Math.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "Commands/CommandContext.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace shen
{
    void UIButtonComponent::Update(float dt)
    {
        _current = _idle;
    }

    void UIButtonComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        target.draw(_current, transform);
    }

    void UIButtonComponent::SetIdle(const sf::Sprite& sprite)
    {
        _idle = sprite;
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

        if (const auto screenPos = context.GetVar<sf::Vector2i>("pos"))
        {
            auto window = _node->GetWindow();
            auto systems = window->GetSystemsManager();
            auto renderTargets = systems->GetSystem<SfmlRenderTargetsSystem>();
            if (auto uiTarget = renderTargets->GetRenderTexture("ui"))
            {
                const auto worldPos = uiTarget->mapPixelToCoords(*screenPos);
                const auto& nodeTransform = _node->GetTransform();
                const auto spriteRect = nodeTransform.transformRect(_current.getLocalBounds());
                processed = spriteRect.contains(worldPos);
            }
        }

        return processed;
    }
}
