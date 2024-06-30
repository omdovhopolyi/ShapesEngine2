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
        virtual void Update(float dt);
        virtual void Draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const;
        
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetWindow(UIWindow* window) { _window = window; }
        UIWindow* GetWindow() const { return _window; }

        sf::Transform& GetTransform() { return _transform; }
        void SetTransform(const sf::Transform& transform) { _transform = transform; }

        UINode* AddChild(const std::string& name);
        UINode* GetChild(const std::string& name);

        template<class Comp>
        Comp* AddComponent()
        {
            const auto typeIndex = std::type_index(typeid(Comp));
            auto component = std::make_shared<Comp>();
            _components[typeIndex] = component;
            return component.get();
        }

        template<class Comp>
        void RemoveComponent()
        {
            const auto typeIndex = std::type_index(typeid(Comp));
            _components.erase(typeIndex);
        }

    protected:
        void OnDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        void OnUpdate(float dt);

    protected:
        std::string _name;
        sf::Transform _transform;
        std::vector<std::shared_ptr<UINode>> _children;
        std::weak_ptr<UINode> _parent;
        std::map<std::type_index, std::shared_ptr<UIComponent>> _components;
        UIWindow* _window = nullptr;
    };
}
