#pragma once

#include <string>

namespace sf
{
    class RenderTarget;
    class Transform;
}

namespace shen
{
    class UINode;

    class UIComponent
    {
    public:
        virtual void Init() {};
        virtual void Update(float dt) {};
        virtual void Draw(sf::RenderTarget& target, const sf::Transform& transform) const {};

        void SetName(const std::string& name) { _name = name; }
        const std::string& GetName() const { return _name; }

        void SetNode(UINode* node) { _node = node; }
        UINode* GetNode() const { return _node; }

    protected:
        UINode* _node = nullptr;
        std::string _name;
        bool _dirty = true;
    };
}
