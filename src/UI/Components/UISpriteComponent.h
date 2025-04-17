#pragma once

#include "UIComponent.h"
#include "Serialization/LoaderMacro.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

namespace shen
{
    class UINode;

    class UISpriteComponent
        : public UIComponent
    {
        CLASS_LOADER_TEST(UISpriteComponent)

    public:
        void RegisterProperties() override;

        void Update(float dt) override;
        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetTexture(sf::Texture* texture);

        void SetTextureRect(const sf::IntRect& rect);

        void SetFillScreen(bool fill);
        bool IsFillScreen() const;

        void SetColor(const sf::Color& color);
        sf::Color GetColor() const;

    protected:
        void CalculateFillSize();

    protected:
        sf::Sprite _sprite;
        sf::Color _color;
        bool _fillScreen = false;
    };
}
