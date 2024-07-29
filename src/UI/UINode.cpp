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

    void UINode::SetId(const std::string& id)
    {
        _id = id;
    }

    const std::string& UINode::GetId() const
    {
        return _id;
    }

    UINode* UINode::AddChild(const std::string& name)
    {
        return AddChildPtr(name).get();
    }

    UINode* UINode::GetChild(const std::string& name)
    {
        const auto& node = GetChildPtr(name);
        if (node)
        {
            return node.get();
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

    const std::shared_ptr<UINode>& UINode::AddChildPtr(const std::string& name)
    {
        _children.emplace_back(std::make_shared<UINode>());
        _children.back()->SetName(name);
        return _children.back();
    }

    const std::shared_ptr<UINode>& UINode::GetChildPtr(const std::string& name)
    {
        auto it = std::find_if(_children.begin(), _children.end(), [name](const auto& node)
        {
            return node->GetName() == name;
        });

        if (it != _children.end())
        {
            return *it;
        }

        static std::shared_ptr<UINode> empty;
        return empty;
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
