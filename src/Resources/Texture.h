#pragma once

#include <string>
#include <glm/glm.hpp>

namespace shen
{
    class Texture
    {
    public:
        void SetPath(const std::string& path) { _path = path; }
        const std::string& GetPath() const { return _path; }

        void SetSize(const glm::ivec2 size) { _size = size; }
        glm::ivec2 GetSize() const { return _size; }

        void SetId(unsigned int id) { _id = id; }
        unsigned int GetId() const { return _id; }

    private:
        std::string _path;
        unsigned int _id = 0;
        glm::ivec2 _size;
    };
}
