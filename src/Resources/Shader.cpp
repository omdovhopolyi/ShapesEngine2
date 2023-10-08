#include "Shader.h"

#include <glad/glad.h>

namespace shen
{
    void Shader::Use()
    {
        glUseProgram(_id);
    }

    void Shader::SetUniform(const std::string& uniformId, const glm::vec2& UV)
    {
        glUniform2fv(glGetUniformLocation(_id, uniformId.c_str()), 1, &UV[0]);
    }

    void Shader::SetUniform(const std::string& uniformId, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, uniformId.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}
