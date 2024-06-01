#pragma once

#include "Window.h"
#include "UINode.h"
#include <SFML/Graphics/Sprite.hpp>

namespace shen
{
    class SfmlUIWindow
        : public Window
    {
    public:
        void Update(float dt) override;
        void Draw() override;

    private:
        std::unique_ptr<UINode> _root;
    };
}
