#include "SfmlSpriteRenderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Render.h"
#include "Messenger/Events/Rendering.h"

namespace shen
{
    void SfmlSpriteRenderSystem::Init(SystemsManager* systems)
    {
        RenderSystem::Init(systems);
        InitSubscriptions();
    }

    void SfmlSpriteRenderSystem::Draw()
    {
        auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>();
        auto window = windowSystem->GetRenderWindow();
        auto& world = _systems->GetWorld();

        world.Each<Sprite, Transform>([&](const auto entity, Sprite& sprite, Transform& transform)
        {
            sprite.sprite.setPosition(transform.position);
            sprite.sprite.setRotation(transform.rotation);
            sprite.sprite.setScale(transform.scale);

            window->draw(sprite.sprite);
        });
    }

    void SfmlSpriteRenderSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<UpdateTexRect>([&](const UpdateTexRect& message)
        {
            auto& world = _systems->GetWorld();
            if (auto sprite = world.GetComponent<Sprite>(message.entity))
            {
                sprite->sprite.setTextureRect(message.texRect);
            }
        });
    }
}
