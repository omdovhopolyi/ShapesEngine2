#include "Render.h"
#include "ECS/World.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void Sprite::Load(Sprite& component, Serialization& serialization)
    {
        if (auto texture = serialization.LoadTexturePtr("texture"))
        {
            auto rect = serialization.LoadIntRect("rect");
            auto anchor = serialization.LoadVec2("anchor");
            auto size = serialization.LoadVec2("size");

            component.sprite.setTexture(*texture);
            component.sprite.setTextureRect(rect);
            component.sprite.setOrigin(anchor);
        }
    }

    void Sprite::Save(Serialization& serialization)
    {

    }

    void Color::Load(Color& component, Serialization& serialization)
    {
        component.color = serialization.LoadColor("color");
    }

    void Color::Save(Serialization& serialization)
    {

    }

    void SpriteFrameAnimation::Load(SpriteFrameAnimation& component, Serialization& serialization)
    {
        component.frameTime = serialization.LoadFloat("frameTime", component.frameTime);
        component.frames = serialization.LoadVectorRect("frames");
    }

    void SpriteFrameAnimation::Save(Serialization& serialization)
    {

    }
}
