#pragma once

#include <string>
#include <glm/glm.hpp>

namespace shen
{
    class Texture
    {
    public:
        const std::string& GetPath() const;
        glm::vec2 GetSize() const;

    private:
        std::string _path;
        glm::vec2 _size;
    };
}
