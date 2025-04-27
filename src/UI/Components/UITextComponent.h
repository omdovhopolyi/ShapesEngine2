#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace shen
{
    class UITextComponent
        : public UIComponent
    {
        SERIALIZABLE(UITextComponent)

    public:
        void RegisterProperties() override;
        void AfterLoad() override;

        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetText(const std::string& text);
        std::string GetText() const;

        void SetFont(const sf::Font& font);

        void SetSize(int size);
        int GetSize() const;

        void SetColor(sf::Color color);
        sf::Color GetColor() const;

        void SetSpacing(float spacing);
        float GetSpacing() const;


    private:
        sf::Text _text;

        std::string _string;
        sf::Font _font;
        int _size = 14;
        sf::Color _color;
        float _spacing = 1.f;
    };
}
