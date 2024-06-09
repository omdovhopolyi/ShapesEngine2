#include "UISpriteComponent.h"
#include "UI/UIWindow.h"
#include "UI/UINode.h"
#include "Utils/Math.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace shen
{
    void UISpriteComponent::Update(float dt)
    {
        if (_dirty)
        {
            _dirty = false;

            if (_fillScreen && _node)
            {
                auto window = _node->GetWindow();
                auto systems = window->GetSystemsManager();
                auto& world = systems->GetWorld();

                auto renderTargets = systems->GetSystem<SfmlRenderTargetsSystem>();
                auto target = renderTargets->GetRenderTexture("ui");
                auto targetSize = target->getSize();

                auto spriteSize = _sprite.getGlobalBounds();
                sf::Vector2f scaleDiff;
                scaleDiff.x = targetSize.x / spriteSize.width;
                scaleDiff.y = targetSize.y / spriteSize.height;

                auto scale = _sprite.getScale();
                scale.x *= scaleDiff.x;
                scale.y *= scaleDiff.y;

                _sprite.setScale(scale);
            }
        }
    }

    void UISpriteComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        target.draw(_sprite, transform);
    }

    void UISpriteComponent::SetTexture(sf::Texture* texture)
    {
        _sprite.setTexture(*texture);
    }

    void UISpriteComponent::SetSprite(const sf::Sprite& sprite)
    {
        _sprite = sprite;
    }

    sf::Sprite& UISpriteComponent::GetSprite()
    {
        return _sprite;
    }

    void UISpriteComponent::SetFillScreen(bool fill)
    {
        _fillScreen = fill;
    }

    bool UISpriteComponent::IsFillScreen() const
    {
        return _fillScreen;
    }
}
