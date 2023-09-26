#pragma once

#include "Sprite.h"

namespace shen
{
    const Texture* Sprite::GetTexture() const
    {
        return _texture;
    }

    glm::vec2 Sprite::GetOrigin() const
    {
        return _origin;
    }

    glm::vec2 Sprite::GetSize() const
    {
        return _size;
    }

    glm::vec2 Sprite::GetLB() const
    {
        return _origin;
    }

    glm::vec2 Sprite::GetRT() const
    {
        return _origin + _size;
    }
}
