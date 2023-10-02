#include "OpenGLSpriteRenderSystem.h"

#include "Game/ManagersProvider.h"

#include "ECS/EcsWorld.h"
#include "ECS/Components/Common.h"

#include "Resources/Texture.h"
#include "Resources/ShadersManager.h"

#include <GL/glew.h>
//#include <glad/glad.h>

namespace shen
{
	void OpenGLSpriteRenderSystem::Start()
	{
        constexpr float vertices[] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        constexpr unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

		auto world = ManagersProvider::Instance().GetWorld();
		
		world->Each<Sprite>(
			[&](const auto entity, Sprite& sprite)
		{
            glGenVertexArrays(1, &sprite.VAO);
            glGenBuffers(1, &sprite.VBO);
            glGenBuffers(1, &sprite.EBO);

            glBindVertexArray(sprite.VAO);

            glBindBuffer(GL_ARRAY_BUFFER, sprite.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
		});
	}

    void OpenGLSpriteRenderSystem::Draw()
    {
		auto world = ManagersProvider::Instance().GetWorld();
        auto shaders = ManagersProvider::Instance().GetOrCreateAssetsManager<ShadersManager>();
		//auto camera = ManagersProvider::Instance().GetCamera();

		world->Each<Sprite>(
			[&](const auto entity, Sprite& sprite)
		{
            if (auto shader = shaders->GetAsset(sprite.shader))
            {
                shader->Use();

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, sprite.texture->GetId());

                glBindVertexArray(sprite.VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
            }
		});
    }
}
