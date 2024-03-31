#include "Shader.h"

#include <glad/glad.h>

namespace shen
{
    void Shader::Use()
    {
        glUseProgram(_id);
    }

    void Shader::SetUniform(const std::string& uniformId, const glm::vec2& vec)
    {
        glUniform2fv(glGetUniformLocation(_id, uniformId.c_str()), 1, &vec[0]);
    }

    void Shader::SetUniform(const std::string& uniformId, const glm::vec4& vec)
    {
        glUniform4fv(glGetUniformLocation(_id, uniformId.c_str()), 1, &vec[0]);
    }

    void Shader::SetUniform(const std::string& uniformId, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, uniformId.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetUniform(const std::string& uniformId, float val)
    {
        glUniform1f(glGetUniformLocation(_id, uniformId.c_str()), val);
    }
}
