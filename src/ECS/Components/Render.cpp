#include "Render.h"
#include "ECS/World.h"
#include "Serialization/Serialization.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"

namespace shen
{
    void Sprite::Load(Sprite& component, Serialization& serialization)
    {
        if (auto textureId = serialization.LoadStr("texture"); !textureId.empty())
        {
            auto systems = serialization.GetSystems();

            if (auto texturesCollection = systems->GetSystem<SfmlTexturesCollection>())
            {
                if (auto texture = texturesCollection->GetTexture(textureId))
                {
                    auto rect = serialization.LoadIntRect("rect");
                    auto anchor = serialization.LoadVec2("anchor");
                    auto size = serialization.LoadVec2("size");

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
            serialization.SaveStr("texture", component.textureId);
            serialization.SaveIntRect("rect", component.sprite.getTextureRect());
            serialization.SaveVec2("size", component.sprite.getOrigin());
        }
    }

    void Color::Load(Color& component, Serialization& serialization)
    {
        component.color = serialization.LoadColor("color");
    }

    void Color::Save(Color& component, Serialization& serialization)
    {
        serialization.SaveColor("color", component.color);
    }

    void SpriteFrameAnimation::Load(SpriteFrameAnimation& component, Serialization& serialization)
    {
        component.frameTime = serialization.LoadFloat("frameTime", component.frameTime);
        component.frames = serialization.LoadVectorRect("frames");
    }

    void SpriteFrameAnimation::Save(SpriteFrameAnimation& component, Serialization& serialization)
    {
        serialization.SaveFloat("frameTime", component.frameTime);
        serialization.SaveVectorRect("frames", component.frames);
    }
}
