#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Transformable.hpp>

namespace shen
{
    class UITransformComponent
        : public UIComponent
    {
    public:
        void Init() override;

        sf::Transform& GetTransform() { return _transform; }
        void SetTransform(const sf::Transform& transform) { _transform = transform; }

        void SetAnchor(const sf::Vector2f& anchor) { _anchor = anchor; }
        sf::Vector2f GetAnchor() const { return _anchor; }

    private:
        sf::Transform _transform;
        sf::Vector2f _anchor;
    };
}
