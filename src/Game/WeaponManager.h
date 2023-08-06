#pragma once

#include "ECS/Entity.h"
#include <glm/glm.hpp>

namespace shen
{
    class WeaponManager
    {
    public:
        void FireBullet(Entity owner, glm::vec3 position, glm::vec3 direction);
    };
}
