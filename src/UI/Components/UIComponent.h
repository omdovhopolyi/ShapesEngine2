#pragma once

#include <string>

namespace sf
{
    class RenderTarget;
    class Transform;
}

namespace shen
{
    class UIComponent
    {
    public:
        virtual void Update(float dt);
        virtual void Draw(sf::RenderTarget& target, const sf::Transform& transform) const;

        void SetName(const std::string& name);
        const std::string& GetName() const;

    protected:
        std::string _name;
    };
}
