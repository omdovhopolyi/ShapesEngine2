#include "UISpriteComponent.h"
#include "UI/UIWindow.h"
#include "UI/UINode.h"
#include "Utils/Math.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Components/Common.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Serialization/Types/SerializableFieldSprite.h"
#include "Serialization/Types/SerializableFieldBool.h"
#include "Serialization/Types/SerializableFieldColor.h"

namespace shen
{
    REGISTER_CLASS_LOADER_TEST(UISpriteComponent);

    void UISpriteComponent::RegisterProperties()
    {
        UIComponent::RegisterProperties();

        RegisterVar<SerializableFieldSprite>(_sprite, "sprite");
        RegisterVar<SerializableFieldBool>(_fillScreen, "fill");
        RegisterVar<SerializableFieldColor>(_color, "color");
    }

    void UISpriteComponent::AfterLoad()
    {
        if (_color != sf::Color::Transparent)
        {
            SetColor(_color);
        }
    }

    void UISpriteComponent::Update(float dt)
    {
        if (_fillScreen)
        {
            CalculateFillSize();
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

    void UISpriteComponent::SetTextureRect(const sf::IntRect& rect)
    {
        _sprite.setTextureRect(rect);
    }

    void UISpriteComponent::SetFillScreen(bool fill)
    {
        _fillScreen = fill;
    }

    bool UISpriteComponent::IsFillScreen() const
    {
        return _fillScreen;
    }

    void UISpriteComponent::SetColor(const sf::Color& color)
    {
        _sprite.setColor(color);
    }

    sf::Color UISpriteComponent::GetColor() const
    {
        return _sprite.getColor();
    }

    void UISpriteComponent::CalculateFillSize()
    {
        auto window = _node->GetWindow();
        auto systems = window->GetSystemsManager();

        auto renderTargets = systems->GetSystem<SfmlRenderTargetsSystem>();
        auto target = renderTargets->GetRenderTexture(SfmlRenderTargetsSystem::UITargetId);
        auto targetSize = target->getSize();

        auto spriteSize = _sprite.getGlobalBounds();
        sf::Vector2f scaleDiff;
        scaleDiff.x = targetSize.x / spriteSize.width;
        scaleDiff.y = targetSize.y / spriteSize.height;

        auto scale = _sprite.getScale();
        scale.x *= scaleDiff.x;
        scale.y *= scaleDiff.y;

        _sprite.setScale(scale);
    }
}
