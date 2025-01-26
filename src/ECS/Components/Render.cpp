#include "Render.h"
#include "ECS/World.h"
#include "Serialization/Serialization.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"

namespace shen
{
    void Sprite::Load(Sprite& component, const Serialization& serialization)
    {
        if (auto textureId = serialization.GetStr("texture"); !textureId.empty())
        {
            auto systems = serialization.GetSystems();

            if (auto texturesCollection = systems->GetSystem<SfmlTexturesCollection>())
            {
                if (auto texture = texturesCollection->GetTexture(textureId))
                {   
                    auto textureSize = texture->getSize();

                    auto rect = serialization.GetIntRect("rect", { 0, 0, static_cast<int>(textureSize.x), static_cast<int>(textureSize.y) });
                    auto anchor = serialization.GetVec2("anchor", { textureSize.x / 2.f, textureSize.y / 2.f });

                    component.textureId = textureId;
                    component.sprite.setTexture(*texture);
                    component.sprite.setTextureRect(rect);
                    component.sprite.setOrigin(anchor);
                }
            }   
        }

        component.sorting = serialization.GetInt("sorting");
    }

    void Sprite::Save(Sprite& component, Serialization& serialization)
    {
        if (auto texture = component.sprite.getTexture())
        {
            serialization.SetStr("texture", component.textureId);
            serialization.SetIntRect("rect", component.sprite.getTextureRect());
            serialization.SetVec2("size", component.sprite.getOrigin());
            serialization.SetInt("sorting", component.sorting);
        }
    }

    void Color::Load(Color& component, const Serialization& serialization)
    {
        component.color = serialization.GetColor("color");
    }

    void Color::Save(Color& component, Serialization& serialization)
    {
        serialization.SetColor("color", component.color);
    }

    void SpriteFrameAnimation::Load(SpriteFrameAnimation& component, const Serialization& serialization)
    {
        component.frameTime = serialization.GetFloat("frameTime", component.frameTime);
        component.frames = serialization.GetVectorIntRect("frames");
    }

    void SpriteFrameAnimation::Save(SpriteFrameAnimation& component, Serialization& serialization)
    {
        serialization.SetFloat("frameTime", component.frameTime);
        serialization.SetVectorIntRect("frames", component.frames);
    }

    /*void Sorting::Load(Sorting& component, const Serialization& serialization)
    {
        component.value = serialization.GetInt("value");
    }

    void Sorting::Save(Sorting& component, Serialization& serialization)
    {
        serialization.SetInt("value", component.value);
    }*/
}
