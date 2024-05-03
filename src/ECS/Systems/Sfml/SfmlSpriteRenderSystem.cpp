#include "SfmlSpriteRenderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Render.h"

namespace shen
{
    void SfmlSpriteRenderSystem::Draw()
    {
        auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>();
        auto window = windowSystem->GetRenderWindow();
        auto& world = _systems->GetWorld();

        world.Each<Sprite, Transform>([&](const auto entity, Sprite& sprite, Transform& transform)
        {
            sprite.sprite.setOrigin(transform.origin);
            sprite.sprite.setPosition(transform.position);
            sprite.sprite.setRotation(transform.rotation);
            sprite.sprite.setScale(transform.scale);

            window->draw(sprite.sprite);
        });
    }
}
