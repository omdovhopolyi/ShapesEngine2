#include "Render.h"
#include "ECS/World.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void Sprite::Load(Entity entity, World* world, const tinyxml2::XMLElement* element)
    {
        auto comp = world->AddComponent<Sprite>(entity);

        comp->texture = LoadTexturePtr("texture", element);
        comp->mask = LoadTexturePtr("mask", element);
        comp->texRect = LoadRect("rect", element);
        comp->size = LoadVec2("size", element, comp->size);
        comp->anchor = LoadVec2("anchor", element);
        comp->shader = LoadShaderPtr("shader", element);

        if (const auto typeStr = LoadStr("spriteType", element); !typeStr.empty())
        {
            comp->spriteType = SpriteTypeEnum.FromString(LoadStr("spriteType", element));
        }
    }

    void Sprite::Save(Entity entity, World* world, tinyxml2::XMLElement* element)
    {

    }

    void Color::Load(Entity entity, World* world, const tinyxml2::XMLElement* element)
    {
        auto comp = world->AddComponent<Color>(entity);

        comp->rgba = LoadColor("color", element) / 255.f;
    }

    void Color::Save(Entity entity, World* world, tinyxml2::XMLElement* element)
    {

    }

    void SpriteFrameAnimation::Load(Entity entity, World* world, const tinyxml2::XMLElement* element)
    {
        auto comp = world->AddComponent<SpriteFrameAnimation>(entity);

        comp->frameTime = LoadFloat("frameTime", element, comp->frameTime);
        comp->frames = LoadVectorRect("frames", element);
    }

    void SpriteFrameAnimation::Save(Entity entity, World* world, tinyxml2::XMLElement* element)
    {

    }
}
