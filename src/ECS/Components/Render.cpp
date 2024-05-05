#include "Render.h"
#include "ECS/World.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void Sprite::Load(Sprite& component, Serialization& serialization)
    {
        /*comp->textureId = LoadStr("textureId", element);


        comp->texture = LoadTexturePtr("texture", element);
        comp->mask = LoadTexturePtr("mask", element);
        comp->texRect = LoadRect("rect", element);
        comp->size = LoadVec2("size", element, comp->size);
        comp->anchor = LoadVec2("anchor", element);
        comp->shader = LoadShaderPtr("shader", element);

        if (const auto typeStr = LoadStr("spriteType", element); !typeStr.empty())
        {
            comp->spriteType = SpriteTypeEnum.FromString(LoadStr("spriteType", element));
        }*/
    }

    void Sprite::Save(Serialization& serialization)
    {

    }

    void Color::Load(Color& component, Serialization& serialization)
    {
        //comp->rgba = LoadColor("color", element) / 255.f;
    }

    void Color::Save(Serialization& serialization)
    {

    }

    void SpriteFrameAnimation::Load(SpriteFrameAnimation& component, Serialization& serialization)
    {
        component.frameTime = serialization.LoadFloat("frameTime", component.frameTime);
        //comp->frames = LoadVectorRect("frames", element);
    }

    void SpriteFrameAnimation::Save(Serialization& serialization)
    {

    }
}
