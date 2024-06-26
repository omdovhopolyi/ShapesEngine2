#include "OpenGLSpriteRenderSystem.h"
//#include "Game/ManagersProvider.h"
//#include "ECS/World.h"
//#include "ECS/Components/Common.h"
//#include "ECS/Components/Render.h"
//#include "Resources/Texture.h"
//#include "Resources/ShadersManager.h"
//#include "Messenger/Events/Rendering.h"
//#include "OpenGLCoords.h"
//
//#include <glad/glad.h>
//#include <glm/gtc/matrix_transform.hpp>
//
//namespace shen
//{
//	void OpenGLSpriteRenderSystem::Start()
//	{
//        InitSubscriptions();
//        InitBuffers();
//	}
//
//    void OpenGLSpriteRenderSystem::Draw()
//    {
//        const Camera* camera = nullptr;
//
//		auto world = ManagersProvider::Instance().GetWorld();
//
//        world->Each<Camera>([&](auto entity, const Camera& comp)
//        {
//            camera = &comp;
//        });
//
//        if (!camera)
//        {
//            return;
//        }
//
//        world->Each<Sprite, Buffers, Transform>(
//            [&](const auto entity, const Sprite& sprite, const Buffers& buffers, const Transform& transform)
//        {
//            if (sprite.shader)
//            {
//                sprite.shader->Use();
//
//                glm::vec3 size = glm::vec3(sprite.size, 1.f) * transform.scale;
//
//                auto model = glm::translate(glm::mat4(1.f), transform.position);
//
//                model = glm::rotate(model, glm::radians(transform.GetEulerAngleZ()), glm::vec3(0.f, 0.f, 1.f));
//                model = glm::translate(model, glm::vec3(-sprite.anchor.x * size.x, -sprite.anchor.y * size.y, 0.f));
//                model = glm::scale(model, size);
//
//                sprite.shader->SetUniform("model", model);
//                sprite.shader->SetUniform("view", camera->view);
//                sprite.shader->SetUniform("projection", camera->projection);
//
//                glm::vec4 rgba = glm::vec4(1.f);
//
//                if (auto color = world->GetComponent<Color>(entity))
//                {
//                    rgba = color->rgba;
//                }
//
//                sprite.shader->SetUniform("color", rgba);
//
//                if (sprite.texture)
//                {
//                    glActiveTexture(GL_TEXTURE0);
//                    glBindTexture(GL_TEXTURE_2D, sprite.texture->GetId());
//                }
//
//                if (sprite.mask)
//                {
//                    glActiveTexture(GL_TEXTURE1);
//                    glBindTexture(GL_TEXTURE_2D, sprite.mask->GetId());
//                }
//
//                glBindVertexArray(buffers.VAO);
//                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//            }
//		});
//    }
//
//    void OpenGLSpriteRenderSystem::InitSubscriptions()
//    {
//        _subscriptions.Subscribe<UpdateTexRect>([this](const UpdateTexRect& message)
//        {
//            auto world = ManagersProvider::Instance().GetWorld();
//            const auto sprite = world->GetComponent<Sprite>(message.entity);
//            const auto buffers = world->GetComponent<Buffers>(message.entity);
//
//            if (!sprite->texture)
//            {
//                return;
//            }
//
//            auto texSize = sprite->texture->GetSize();
//            
//            const auto left = sprite->texRect.Left() / texSize.x;
//            const auto bottom = sprite->texRect.Bottom() / texSize.y;
//            const auto right = sprite->texRect.Right() / texSize.x;
//            const auto top = sprite->texRect.Top() / texSize.y;
//
//            const float UV[] = {
//                left, bottom,
//                right, bottom,
//                right, top,
//                left, top
//            };
//
//            glBindBuffer(GL_ARRAY_BUFFER, buffers->UV);
//            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(UV), UV);
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
//        });
//    }
//
//    void OpenGLSpriteRenderSystem::InitBuffers()
//    {
//        auto world = ManagersProvider::Instance().GetWorld();
//
//        world->Each<Sprite>(
//            [&](const auto entity, Sprite& sprite)
//        {
//            if (!sprite.texture)
//            {
//                return;
//            }
//
//            auto buffers = world->AddComponent<Buffers>(entity);
//
//            glGenVertexArrays(1, &buffers->VAO);
//            glGenBuffers(1, &buffers->VBO);
//            glGenBuffers(1, &buffers->UV);
//            glGenBuffers(1, &buffers->EBO);
//
//            glBindVertexArray(buffers->VAO);
//
//            glBindBuffer(GL_ARRAY_BUFFER, buffers->VBO);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
//            glEnableVertexAttribArray(0);
//
//            auto texSize = sprite.texture->GetSize();
//
//            const auto left = sprite.texRect.Left() / texSize.x;
//            const auto bottom = sprite.texRect.Bottom() / texSize.y;
//            const auto right = sprite.texRect.Right() / texSize.x;
//            const auto top = sprite.texRect.Top() / texSize.y;
//
//            const float UV[] = {
//                left, bottom,
//                right, bottom,
//                right, top,
//                left, top
//            };
//
//            glBindBuffer(GL_ARRAY_BUFFER, buffers->UV);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);
//
//            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
//            glEnableVertexAttribArray(1);
//
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->EBO);
//            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
//            glBindVertexArray(0);
//        });
//    }
//}
