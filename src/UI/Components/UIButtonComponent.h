#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class UIButtonComponent
        : public UIComponent
    {
    public:
        void Update(float dt) override;
        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetIdle(const sf::Sprite& sprite);
        sf::Sprite& GetIdle();

        void SetPressed(const sf::Sprite& sprite);
        sf::Sprite& GetPressed();

        void SetHovered(const sf::Sprite& sprite);
        sf::Sprite& GetHovered();

    private:
        sf::Sprite _current;
        sf::Sprite _idle;
        sf::Sprite _pressed;
        sf::Sprite _hovered;
    };
}
