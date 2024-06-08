#include "UISpriteComponent.h"
#include "UI/UIWindow.h"
#include "UI/UINode.h"
#include "Utils/Math.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace shen
{
    void UISpriteComponent::Update(float dt)
    {
        if (_fillScreen)
        {
            if (_node)
            {
                auto window = _node->GetWindow();
                auto systems = window->GetSystemsManager();
                auto& world = systems->GetWorld();

                bool found = false;
                sf::Vector2f cameraSize;
                sf::Vector2f cameraCenter;

                world.Each<Camera>([&](auto entity, const Camera& camera)
                {
                    if (!found)
                    {
                        cameraSize = camera.view.getSize();
                        cameraCenter = camera.view.getCenter();
                        found = true;
                    }
                });

                if (found)
                {
                    cameraSize.x = std::abs(cameraSize.x);
                    cameraSize.y = std::abs(cameraSize.y);

                    auto spriteSize = _sprite.getGlobalBounds();
                    sf::Vector2f scaleDiff;
                    scaleDiff.x = cameraSize.x / spriteSize.width;
                    scaleDiff.y = cameraSize.y / spriteSize.height;

                    auto scale = _sprite.getScale();
                    scale.x *= scaleDiff.x;
                    scale.y *= scaleDiff.y;

                    _sprite.setScale(scale);

                    auto pos = cameraCenter - (cameraSize / 2.f);

                    _sprite.setPosition(pos);
                }
            }
        }
    }

    void UISpriteComponent::Draw(sf::RenderTarget& target, const sf::Transform& transform) const
    {
        target.draw(_sprite, transform);
    }

    void UISpriteComponent::SetTexture(sf::Texture* texture)
    {
        _sprite.setTexture(*texture);
    }

    void UISpriteComponent::SetSprite(const sf::Sprite& sprite)
    {
        _sprite = sprite;
    }

    sf::Sprite& UISpriteComponent::GetSprite()
    {
        return _sprite;
    }

    void UISpriteComponent::SetFillScreen(bool fill)
    {
        _fillScreen = fill;
    }

    bool UISpriteComponent::IsFillScreen() const
    {
        return _fillScreen;
    }
}
