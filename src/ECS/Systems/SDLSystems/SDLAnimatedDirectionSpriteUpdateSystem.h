#pragma once

#include "ECS/Systems/System.h"
#include "Utils/Types.h"

#include <glm/glm.hpp>

namespace shen
{
    class SDLAnimatedDirectionSpriteUpdateSystem
        : public System
    {
    public:
        void Update() override;

    private:
        Range<float> _forwardAngleRange = Range<float>(-45.f, 45.f, RangeType::IncludeBoth);
        Range<float> _rightAngleRange = Range<float>(45.f, 135.f, RangeType::ExcludeBoth);
        Range<float> _leftAngleRange = Range<float>(-135.f, -45.f, RangeType::ExcludeBoth);

        glm::vec2 _forward = glm::vec2(0.f, -1.f);
    };
}
