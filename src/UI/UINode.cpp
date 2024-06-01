#include "UINode.h"

namespace shen
{
    void UINode::Update(float dt)
    {
        OnUpdate(dt);
    }

    void UINode::Draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const
    {
        auto combinedTransform = parentTransform * _transform;

        OnDraw(target, combinedTransform);

        for (auto& child : _children)
        {
            child->Draw(target, combinedTransform);
        }
    }

    void UINode::OnDraw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        for (auto& [type, component] : _components)
        {
            component->Draw(target, transform);
        }
    }

    void UINode::OnUpdate(float dt)
    {
        for (auto& [type, component] : _components)
        {
            component->Update(dt);
        }
    }
}
