#include "UITextComponent.h"
#include "Serialization/Types/SerializableFieldString.h"
#include "Serialization/Types/SerializableFieldFont.h"
#include "Serialization/Types/SerializableFieldInt.h"
#include "Serialization/Types/SerializableFieldColor.h"
#include "Serialization/Types/SerializableFieldFloat.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace shen
{
    REGISTER_CLASS_LOADER(UITextComponent);

    void UITextComponent::RegisterProperties()
    {
        UIComponent::RegisterProperties();

        RegisterVar<SerializableFieldString>(_string, "text");
        RegisterVar<SerializableFieldFont>(_font, "font");
        RegisterVar<SerializableFieldInt>(_size, "size");
        RegisterVar<SerializableFieldColor>(_color, "color");
        RegisterVar<SerializableFieldFloat>(_spacing, "spacing");
    }

    void UITextComponent::AfterLoad()
    {
        UIComponent::AfterLoad();

        _text.setString(_string);
        _text.setFont(_font);
        _text.setCharacterSize(_size);
        _text.setColor(_color);
        _text.setLetterSpacing(_spacing);
    }

    void UITextComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        target.draw(_text, transform);
    }

    void UITextComponent::SetText(const std::string& text)
    {
        _string = text;
        _text.setString(text);
    }

    std::string UITextComponent::GetText() const
    {
        return _string;
    }

    void UITextComponent::SetFont(const sf::Font& font)
    {
        _font = font;
        _text.setFont(font);
    }

    void UITextComponent::SetSize(int size)
    {
        _size = size;
        _text.setCharacterSize(size);
    }

    int UITextComponent::GetSize() const
    {
        return _size;
    }

    void UITextComponent::SetColor(sf::Color color)
    {
        _color = color;
        _text.setColor(color);
    }

    sf::Color UITextComponent::GetColor() const
    {
        return _color;
    }

    void UITextComponent::SetSpacing(float spacing)
    {
        _spacing = spacing;
        _text.setLetterSpacing(spacing);
    }

    float UITextComponent::GetSpacing() const
    {
        return _spacing;
    }
}
