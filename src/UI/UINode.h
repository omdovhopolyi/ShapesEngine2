#pragma once

#include "Components/UIComponent.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include <map>
#include <memory>
#include <typeinfo>
#include <typeindex>

namespace shen
{
    class UIWindow;

    class UINode
    {
    public:
        using SharedPtr = std::shared_ptr<UINode>;
        using WeakPtr = std::weak_ptr<UINode>;

        virtual void Update(float dt);
        virtual void Draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const;
        
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetId(const std::string& id);
        const std::string& GetId() const;

        void SetWindow(UIWindow* window) { _window = window; }
        UIWindow* GetWindow() const { return _window; }

        sf::Transform& GetTransform() { return _transform; }
        void SetTransform(const sf::Transform& transform) { _transform = transform; }

        void SetAnchor(const sf::Vector2f& anchor) { _anchor = anchor; }
        sf::Vector2f GetAnchor() const { return _anchor; }

        UINode* AddChild(const std::string& name);
        UINode* GetChild(const std::string& name);
        void RemoveChild(const std::string& name);
        std::vector<std::shared_ptr<UINode>>& GetChildren() { return _children; }

        const std::shared_ptr<UINode>& AddChildPtr(const std::string& name);
        const std::shared_ptr<UINode>& GetChildPtr(const std::string& name);

        template<class Comp>
        std::shared_ptr<Comp> AddComponent()
        {
            const auto typeIndex = std::type_index(typeid(Comp));
            auto component = std::make_shared<Comp>();
            _components[typeIndex] = component;
            return component;
        }

        template<class Comp>
        std::shared_ptr<Comp> GetComponent()
        {
            const auto typeIndex = std::type_index(typeid(Comp));
            if (auto it = _components.find(typeIndex); it != _components.end())
            {
                return std::static_pointer_cast<Comp>(it->second);
            }
            return nullptr;
        }

        template<class Comp>
        void RemoveComponent()
        {
            const auto typeIndex = std::type_index(typeid(Comp));
            _components.erase(typeIndex);
        }

        std::map<std::type_index, std::shared_ptr<UIComponent>>& GetComponents() { return _components; }

    protected:
        void OnDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        void OnUpdate(float dt);

    protected:
        std::string _name;
        std::string _id;
        sf::Transform _transform;
        sf::Vector2f _anchor;
        std::vector<std::shared_ptr<UINode>> _children;
        std::weak_ptr<UINode> _parent;
        std::map<std::type_index, std::shared_ptr<UIComponent>> _components;
        UIWindow* _window = nullptr;
    };
}
