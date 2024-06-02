#pragma once

#include "UIComponent.h"
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class UINode;

    class UISpriteComponent
        : public UIComponent
    {
    public:
        void Update(float dt) override;
        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetTexture(sf::Texture* texture);

        void SetSprite(const sf::Sprite& sprite);
        sf::Sprite& GetSprite();

        void SetFillScreen(bool fill);
        bool IsFillScreen() const;

        void SetNode(UINode* node) { _node = node; }
        UINode* GetNode() const { return _node; }

    private:
        UINode* _node = nullptr;
        sf::Sprite _sprite;
        bool _fillScreen = false;
    };
}
