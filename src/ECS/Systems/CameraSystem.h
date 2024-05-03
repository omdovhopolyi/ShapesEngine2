#pragma once

#include "BaseSystems/UpdateSystem.h"
//#include <glm/glm.hpp>
#include <SFML/System/Vector2.hpp>

namespace shen
{
    class CameraSystem
        : public UpdateSystem
    {
    public:
        void Start() override;
        void Update() override;

    private:
        sf::Vector2f _viewportSize;
    };
}
