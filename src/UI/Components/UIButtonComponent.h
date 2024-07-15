#pragma once

#include "UIInputComponent.h"
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class UIButtonComponent
        : public UIInputComponent
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

        bool ProcessInput(const InputType& inputType, const CommandContext& context) override;

    private:
        sf::Sprite _current;
        sf::Sprite _idle;
        sf::Sprite _pressed;
        sf::Sprite _hovered;
    };
}
