#include "SfmlSpriteRenderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/Systems/Sfml/SfmlRenderTexturesSystem.h"
#include "ECS/Systems/Sfml/SfmlRenderTexturesSystem.h"
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

    void SfmlSpriteRenderSystem::Start()
    {

    }

    void SfmlSpriteRenderSystem::Draw()
    {
        auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>();
        auto window = windowSystem->GetRenderWindow();
        auto& world = _systems->GetWorld();

        auto renderTextures = _systems->GetSystem<SfmlRenderTexturesSystem>();
        auto target = renderTextures->GetRenderTexture("world"); // TODO check target

        const auto& view = window->getView();
        const auto center = view.getCenter();
        const auto size = view.getSize();
        sf::FloatRect viewBounds;
        viewBounds.width = size.x;
        viewBounds.height = size.y;
        viewBounds.left = center.x - size.x / 2.f;
        viewBounds.top = center.y - size.y / 2.f;

        target->clear();
        
        world.Each<Sprite, Transform>([&](const auto entity, Sprite& sprite, Transform& transform)
        {
            sprite.sprite.setPosition(transform.position);
            sprite.sprite.setRotation(transform.rotation);
            sprite.sprite.setScale(transform.scale);

            const auto spriteBounds = sprite.sprite.getGlobalBounds();
            const bool isVisible = viewBounds.intersects(spriteBounds);

            if (isVisible)
            {
                target->draw(sprite.sprite);
            }
        });

        target->display();
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
