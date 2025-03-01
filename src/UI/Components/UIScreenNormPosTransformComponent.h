#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Transformable.hpp>

namespace shen
{
    class UIScreenNormPosTransformComponent
        : public UIComponent
    {
    public:
        void Init() override;
        void Update(float) override;

        const sf::Vector2f& GetNormPosition() const { return _normPosition; }
        void SetNormPosition(const sf::Vector2f& normPosition) { _normPosition = normPosition; }

        float GetAngle() const { return _angle; }
        void SetAngle(float angle) { _angle = angle; }

        const sf::Vector2f& GetScale() const { return _anchor; }
        void SetScale(const sf::Vector2f& scale) { _scale = scale; }

        const sf::Vector2f& GetAnchor() const { return _anchor; }
        void SetAnchor(const sf::Vector2f& pos) { _anchor = pos; }

        void SetDirty(bool dirty) { _dirty = dirty; }
        bool IsDirty() const { return _dirty; }

    private:
        void UpdatePosition();

    private:
        sf::Vector2f _normPosition;
        float _angle = 0.f;
        sf::Vector2f _scale;
        sf::Vector2f _anchor;
        bool _dirty = true;
    };
}

