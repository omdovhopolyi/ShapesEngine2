#include "UINode.h"

namespace shen
{
    void UINode::Update(float dt)
    {
        OnUpdate(dt);

        for (auto& child : _children)
        {
            child->Update(dt);
        }
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

    void UINode::SetName(const std::string& name)
    {
        _name = name;
    }

    const std::string& UINode::GetName() const
    {
        return _name;
    }

    UINode* UINode::AddChild(const std::string& name)
    {
        auto child = std::make_shared<UINode>();
        child->SetName(name);
        _children.push_back(child);
        return child.get();
    }

    UINode* UINode::GetChild(const std::string& name)
    {
        return nullptr;
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
