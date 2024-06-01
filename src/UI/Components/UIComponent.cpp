#include "UIComponent.h"

namespace shen
{
    void UIComponent::Update(float dt)
    {

    }

    void UIComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {

    }

    void UIComponent::SetName(const std::string& name)
    {
        _name = name;
    }

    const std::string& UIComponent::GetName() const
    {
        return _name;
    }
}
