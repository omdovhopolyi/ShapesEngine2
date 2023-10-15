#pragma once

#include <string>
#include <glm/glm.hpp>

namespace shen
{
    class Shader
    {
    public:
        void Use();

        void SetId(unsigned int id) { _id = id; }
        unsigned int GetId() const { return _id; }

        void SetUniform(const std::string& uniformId, const glm::vec2& UV);
        void SetUniform(const std::string& uniformId, const glm::mat4& mat);

    private:
        unsigned int _id = 0;
    };
}
