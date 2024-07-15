#include "UINode.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/UIEvents.h"
#include "UIWindow.h"

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
        auto it = std::find_if(_children.begin(), _children.end(), [name](const auto& node)
        {
            return node->GetName() == name;
        });

        if (it != _children.end())
        {
            return it->get();
        }

        return nullptr;
    }

    void UINode::RemoveChild(const std::string& name)
    {
        auto it = std::remove_if(_children.begin(), _children.end(), [name](const auto& node)
        {
            return node->GetName() == name;
        });

        _children.erase(it);

        Messenger::Instance().Broadcast<InputComponentsDirty>(_window->GetId());
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
