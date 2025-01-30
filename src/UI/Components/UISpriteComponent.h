#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class UINode;

    class UISpriteComponent
        : public UIComponent
    {
    public:
        void Update(float dt) override;
        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetTexture(sf::Texture* texture);

        void SetFillScreen(bool fill);
        bool IsFillScreen() const;

        void SetColor(const sf::Color& color);
        sf::Color GetColor() const;

    private:
        sf::Sprite _sprite;
        bool _fillScreen = false;
    };
}
