#include "OpenGLGridRenderSystem.h"
#include "Game/ManagersProvider.h"
#include "Resources/ShadersManager.h"
#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"
#include "OpenGLCoords.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace shen
{
    void OpenGLGridRenderSystem::Start()
    {
        InitBuffers();
    }

    void OpenGLGridRenderSystem::Draw()
    {
        const Camera* camera = nullptr;

        auto world = ManagersProvider::Instance().GetWorld();

        world->Each<Camera>([&](auto entity, const Camera& comp)
            {
                camera = &comp;
            });

        if (!camera)
        {
            return;
        }

        auto shadersManager = ManagersProvider::Instance().GetOrCreateAssetsManager<ShadersManager>();
        auto shader = shadersManager->GetAsset("Grid");

        shader->Use();
        
        shader->SetUniform("model", glm::mat4(1.f));
        shader->SetUniform("view", camera->view);
        shader->SetUniform("projection", camera->projection);

        shader->SetUniform("cameraDistance", camera->position.z);
        shader->SetUniform("lineWidth", 0.003f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void OpenGLGridRenderSystem::InitSubscriptions()
    {

    }

    void OpenGLGridRenderSystem::InitBuffers()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gridPlane), gridPlane, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
