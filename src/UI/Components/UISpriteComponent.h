#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class UISpriteComponent
        : public UIComponent
    {
    public:
        void Update(float dt) override;
        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetSprite(const sf::Sprite& sprite);
        const sf::Sprite& GetSprite() const;

    private:
        sf::Sprite _sprite;
    };
}
