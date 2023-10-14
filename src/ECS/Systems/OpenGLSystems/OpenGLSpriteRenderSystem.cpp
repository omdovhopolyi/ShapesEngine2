#include "OpenGLSpriteRenderSystem.h"

#include "Game/ManagersProvider.h"

#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

#include "Resources/Texture.h"
#include "Resources/ShadersManager.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace shen
{
	void OpenGLSpriteRenderSystem::Start()
	{
        constexpr float vertices[] = {
            1.f, 1.f, 0.0f,
            1.f, 0.f, 0.0f,
            0.f, 0.f, 0.0f,
            0.f, 1.f, 0.0f
        };

        /*constexpr float UV[] = {
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,
            0.f, 1.f
        };*/

        constexpr unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

		auto world = ManagersProvider::Instance().GetWorld();
		
		world->Each<Sprite>(
			[&](const auto entity, Sprite& sprite)
		{
            auto buffers = world->AddComponent<Buffers>(entity);

            glGenVertexArrays(1, &buffers->VAO);
            glGenBuffers(1, &buffers->VBO);
            glGenBuffers(1, &buffers->UV);
            glGenBuffers(1, &buffers->EBO);

            glBindVertexArray(buffers->VAO);

            glBindBuffer(GL_ARRAY_BUFFER, buffers->VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
            glEnableVertexAttribArray(0);

            auto texSize = sprite.texture->GetSize();
            auto texOriginUV = sprite.texOrigin / texSize;
            auto texSizeUV = sprite.texSize / texSize;

            const float UV[] = {
                texSizeUV.x, texSizeUV.y,
                texSizeUV.x, texOriginUV.y,
                texOriginUV.x, texOriginUV.y,
                texOriginUV.x, texSizeUV.y,
            };

            glBindBuffer(GL_ARRAY_BUFFER, buffers->UV);
            glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
		});
	}

    void OpenGLSpriteRenderSystem::Draw()
    {
		auto world = ManagersProvider::Instance().GetWorld();
        auto shaders = ManagersProvider::Instance().GetOrCreateAssetsManager<ShadersManager>();

        const CameraComp* cameraComp = nullptr;

        world->Each<CameraComp>([&](auto entity, const CameraComp& camera)
        {
            cameraComp = &camera;
        });

        if (!cameraComp)
        {
            return;
        }

        world->Each<Sprite, Buffers, Transform>(
            [&](const auto entity, const Sprite& sprite, const Buffers& buffers, const Transform& transform)
        {
            if (auto shader = shaders->GetAsset(sprite.shader))
            {
                shader->Use();

                auto model = glm::translate(glm::mat4(1.f), transform.position);

                //glm::vec3 size = glm::vec3(2.f, 2.f, 1.f) * transform.scale;
                glm::vec3 size = glm::vec3(sprite.size, 1.f) * transform.scale;

                model = glm::translate(model, glm::vec3(sprite.anchor.x * size.x, sprite.anchor.y * size.y, 0.f));
                model = glm::rotate(model, glm::radians(transform.GetEulerAngleZ()), glm::vec3(0.f, 0.f, 1.f));
                model = glm::translate(model, glm::vec3(-sprite.anchor.x * size.x, -sprite.anchor.y * size.y, 0.f));
                
                model = glm::scale(model, size);

                shader->SetUniform("model", model);
                shader->SetUniform("view", cameraComp->view);
                shader->SetUniform("projection", cameraComp->projection);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, sprite.texture->GetId());

                glBindVertexArray(buffers.VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
            }
		});
    }
}
