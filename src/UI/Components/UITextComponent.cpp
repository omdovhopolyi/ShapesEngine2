#include "UITextComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace shen
{
    void UITextComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        target.draw(_text, transform);
    }

    void UITextComponent::SetText(const std::string& text)
    {
        _text.setString(text);
    }

    std::string UITextComponent::GetText() const
    {
        return _text.getString();
    }

    void UITextComponent::SetFont(const sf::Font& font)
    {
        _text.setFont(font);
    }

    void UITextComponent::SetSize(unsigned int size)
    {
        _text.setCharacterSize(size);
    }

    unsigned int UITextComponent::GetSize() const
    {
        return _text.getCharacterSize();
    }

    void UITextComponent::SetColor(sf::Color color)
    {
        _text.setColor(color);
    }

    sf::Color UITextComponent::GetColor() const
    {
        return _text.getColor();
    }

    void UITextComponent::SetSpacing(float spacing)
    {
        _text.setLetterSpacing(spacing);
    }

    float UITextComponent::GetSpacing() const
    {
        return _text.getLetterSpacing();
    }
}
