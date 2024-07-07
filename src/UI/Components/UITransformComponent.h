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

    private:
        sf::Transform _transform;
    };
}
