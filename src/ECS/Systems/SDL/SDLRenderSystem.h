#pragma once

#include <ECS/Systems/BaseSystems/RenderSystem.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>

class SDL_Window;

namespace shen
{
    struct Offset
    {
        float x = 0.f;
        float y = 0.f;
    };

    class SDLRenderSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(SDLRenderSystem)

    public:
        void Start() override;
        void Draw() override;

    private:
        void InitVertexShader();
        void InitFragmentShader();
        void InitShaderProgram();
        void ClearShaders();

        //void ProcessInput();

    private:
        SDL_Window* _window = nullptr;
        std::vector<float> _vertices;
        std::vector<unsigned int> _indices;
        std::string _vertexShader;
        std::string _fragmentShader;
        GLuint _vertexShaderID = 0;
        GLuint _fragmentShaderID = 0;
        GLuint _shaderProgram = 0;
        GLuint _vbo = 0;
        GLuint _ebo = 0;
        GLuint _vao = 0;

        Offset _offset;

        GLint _uColor = -1;
        GLint _uOffset = -1;
    };
}
