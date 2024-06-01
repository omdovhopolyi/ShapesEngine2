#include "UISpriteComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace shen
{
    void UISpriteComponent::Update(float dt)
    {
    }

    void UISpriteComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        target.draw(_sprite, transform);
    }

    void UISpriteComponent::SetSprite(const sf::Sprite& sprite)
    {
        _sprite = sprite;
    }

    const sf::Sprite& UISpriteComponent::GetSprite() const
    {
        return _sprite;
    }
}
