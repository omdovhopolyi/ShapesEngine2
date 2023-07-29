#pragma once

#include <glm/glm.hpp>

namespace shen
{
    class WeaponManager
    {
    public:
        void FireBullet(glm::vec3 position, glm::vec3 direction);
    };
}
