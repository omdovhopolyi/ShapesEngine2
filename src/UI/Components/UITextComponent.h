#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace shen
{
    class UITextComponent
        : public UIComponent
    {
    public:
        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetText(const std::string& text);
        const std::string& GetText() const;

        void SetFont(const sf::Font& font);

        void SetSize(unsigned int size);
        unsigned int GetSize() const;

        void SetColor(sf::Color color);
        sf::Color GetColor() const;

    private:
        sf::Text _text;
    };
}
