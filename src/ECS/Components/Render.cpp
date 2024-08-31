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
                    auto rect = serialization.GetIntRect("rect");
                    auto anchor = serialization.GetVec2("anchor");
                    auto size = serialization.GetVec2("size");

                    component.textureId = textureId;
                    component.sprite.setTexture(*texture);
                    component.sprite.setTextureRect(rect);
                    component.sprite.setOrigin(anchor);
                }
            }   
        }
    }

    void Sprite::Save(Sprite& component, Serialization& serialization)
    {
        if (auto texture = component.sprite.getTexture())
        {
            serialization.SetStr("texture", component.textureId);
            serialization.SetIntRect("rect", component.sprite.getTextureRect());
            serialization.SetVec2("size", component.sprite.getOrigin());
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
}
