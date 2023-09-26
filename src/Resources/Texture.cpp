#include "Texture.h"

namespace shen
{
    const std::string& Texture::GetPath() const
    {
        return _path;
    }

    glm::vec2 Texture::GetSize() const
    {
        return _size;
    }
}
