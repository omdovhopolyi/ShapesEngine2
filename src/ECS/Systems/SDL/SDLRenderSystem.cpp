#include <ECS/Systems/SDL/SDLRenderSystem.h>
#include <ECS/Systems/BaseSystems/PlayerWindowInputSystem.h>
#include <ECS/SystemsManager.h>

#include <Logger/Logger.h>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

#include <Messenger/Messenger.h>
#include <Messenger/Events/Common.h>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SDLRenderSystem)

    void SDLRenderSystem::Start()
    {
        InitSubscriptions();

        _vertices = {
            0.5f, 0.5f, 0.f,        1.f, 0.f, 0.f,
            -0.5f, 0.5f, 0.f,       0.f, 1.f, 0.f,
            -0.5f, -0.5f, 0.f,      0.f, 0.f, 1.f,
            0.5f, -0.5f, 0.f,       1.f, 1.f, 0.f
        };

        _indices = {
            0, 1, 2,
            0, 2, 3
        };

        InitVertexShader();
        InitFragmentShader();
        InitShaderProgram();
        ClearShaders();

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(float) * 6, (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        _uColor = glGetUniformLocation(_shaderProgram, "uColor");
        _uOffset = glGetUniformLocation(_shaderProgram, "uOffset");
    }

    void SDLRenderSystem::Draw()
    {
        glUseProgram(_shaderProgram);
        glBindVertexArray(_vao);
        glUniform4f(_uColor, 0.f, 1.f, 0.f, 1.f);
        glUniform2f(_uOffset, _offset.x, _offset.y);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void SDLRenderSystem::InitVertexShader()
    {
        _vertexShader = R"(
            #version 330 core
            layout (location = 0) in vec3 position;
            layout (location = 1) in vec3 color;
            
            out vec3 vColor;      
            uniform vec2 uOffset;      

            void main() {
                gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
                vColor = color;
            }
        )";

        _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderCStr = _vertexShader.c_str();
        glShaderSource(_vertexShaderID, 1, &vertexShaderCStr, nullptr);
        glCompileShader(_vertexShaderID);

        GLint success;
        glGetShaderiv(_vertexShaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(_vertexShaderID, 512, nullptr, infoLog);
            Logger::Err("VERTEX SHADER: COMPILATION: {}", infoLog);
        }
    }

    void SDLRenderSystem::InitFragmentShader()
    {
        _fragmentShader = R"(
            #version 330 core
            
            in vec3 vColor;
            uniform vec4 uColor;
            out vec4 FragColor;
            
            void main() {
                FragColor = vec4(vColor, 1.0) * uColor;
            }
        )";

        _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderCStr = _fragmentShader.c_str();
        glShaderSource(_fragmentShaderID, 1, &fragmentShaderCStr, nullptr);
        glCompileShader(_fragmentShaderID);

        GLint success;
        glGetShaderiv(_fragmentShaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(_fragmentShaderID, 512, nullptr, infoLog);
            Logger::Err("FRAGMENT SHADER: COMPILATION: {}", infoLog);
        }
    }

    void SDLRenderSystem::InitShaderProgram()
    {
        _shaderProgram = glCreateProgram();
        glAttachShader(_shaderProgram, _vertexShaderID);
        glAttachShader(_shaderProgram, _fragmentShaderID);
        glLinkProgram(_shaderProgram);

        GLint success;
        glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(_shaderProgram, 512, nullptr, infoLog);
            Logger::Err("SHADER PROGRAMM: LINK: {}", infoLog);
        }
    }

    void SDLRenderSystem::ClearShaders()
    {
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    void SDLRenderSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const auto& event) {
            auto inputSystem = _systems->GetInput();

            if (event.type == InputEventType::Up) {
                if (inputSystem->GetCharByKey(event.code) == "Up") {
                    _offset.y += 0.01f;
                    Logger::Log("KEY_UP");
                }
                if (inputSystem->GetCharByKey(event.code) == "Down") {
                    _offset.y -= 0.01f;
                    Logger::Log("KEY_DOWN");
                }
                if (inputSystem->GetCharByKey(event.code) == "Right") {
                    _offset.x += 0.01f;
                    Logger::Log("KEY_RIGHT");
                }
                if (inputSystem->GetCharByKey(event.code) == "Left") {
                    _offset.x -= 0.01f;
                    Logger::Log("KEY_LEFT");
                }
            }
        });
    }
}
