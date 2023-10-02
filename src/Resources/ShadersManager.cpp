#include "ShadersManager.h"

#include "Logger/Logger.h"

#include <fstream>
#include <sstream>

//#include <glad/glad.h>
#include <GL/glew.h>

namespace shen
{
    // TODO Refactor

    std::pair<std::unique_ptr<Shader>, bool> ShadersManager::LoadAssetImpl(const LoadParams& params)
    {
        std::string vertexPath;
        std::string fragmentPath;

        if (auto it = params.find("vertexPath"); it != params.end())
        {
            vertexPath = it->second;
        }

        if (auto it = params.find("fragmentPath"); it != params.end())
        {
            fragmentPath = it->second;
        }

        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try 
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            std::stringstream vShaderStream;
            std::stringstream fShaderStream;
            
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            
            vShaderFile.close();
            fShaderFile.close();
            
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            Logger::Err("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: {}", e.what());
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        
        unsigned int vertex = 0;
        unsigned int fragment = 0;
        
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
        
        unsigned int id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        CheckCompileErrors(id, "PROGRAM");
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        auto shader = std::make_unique<Shader>();
        shader->SetId(id);

        return { std::move(shader), true };
    }

    void ShadersManager::CheckCompileErrors(unsigned int shaderId, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
                Logger::Err("ERROR::SHADER_COMPILATION_ERROR of type: {}\n{}\n\n", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shaderId, 1024, NULL, infoLog);
                Logger::Err("ERROR::PROGRAM_LINKING_ERROR of type: {}\n{}\n\n", type, infoLog);
            }
        }
    }
}
