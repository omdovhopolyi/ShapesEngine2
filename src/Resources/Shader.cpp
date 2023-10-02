#include "Shader.h"

//#include <glad/glad.h>
#include <GL/glew.h>

namespace shen
{
    void Shader::Use()
    {
        glUseProgram(_id);
    }
}
