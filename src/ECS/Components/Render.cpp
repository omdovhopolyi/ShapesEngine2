#include "Render.h"
#include "ECS/World.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "ECS/SystemsManager.h"
#include "Serialization/DataElementWrapper.h"

namespace shen
{
    void Sprite::Load(Sprite& component, const DataElementWrapper& elementWrapper)
    {
        if (auto textureId = elementWrapper.GetStr("texture"); !textureId.empty())
        {
            auto systems = elementWrapper.GetSystems();

            if (auto texturesCollection = systems->GetSystem<SfmlTexturesCollection>())
            {
                if (auto texture = texturesCollection->GetTexture(textureId))
                {   
                    auto textureSize = texture->getSize();

                    auto rect = elementWrapper.GetIntRect("rect", { 0, 0, static_cast<int>(textureSize.x), static_cast<int>(textureSize.y) });
                    auto anchor = elementWrapper.GetVec2("anchor", { textureSize.x / 2.f, textureSize.y / 2.f });

                    component.textureId = textureId;
                    component.sprite.setTexture(*texture);
                    component.sprite.setTextureRect(rect);
                    component.sprite.setOrigin(anchor);
                }
            }   
        }

        component.sorting = elementWrapper.GetInt("sorting");
    }

    void Sprite::Save(Sprite& component, DataElementWrapper& elementWrapper)
    {
        if (auto texture = component.sprite.getTexture())
        {
            elementWrapper.SetStr("texture", component.textureId);
            elementWrapper.SetIntRect("rect", component.sprite.getTextureRect());
            elementWrapper.SetVec2("size", component.sprite.getOrigin());
            elementWrapper.SetInt("sorting", component.sorting);
        }
    }

    void Color::Load(Color& component, const DataElementWrapper& elementWrapper)
    {
        component.color = elementWrapper.GetColor("color");
    }

    void Color::Save(Color& component, DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetColor("color", component.color);
    }

    void SpriteFrameAnimation::Load(SpriteFrameAnimation& component, const DataElementWrapper& elementWrapper)
    {
        component.frameTime = elementWrapper.GetFloat("frameTime", component.frameTime);
        component.frames = elementWrapper.GetVectorIntRect("frames");
        component.animType = AnimationTypeEnum.FromString(elementWrapper.GetStr("animType"));
        component.deleteOnDone = elementWrapper.GetBool("deleteOnDone");
    }

    void SpriteFrameAnimation::Save(SpriteFrameAnimation& component, DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetFloat("frameTime", component.frameTime);
        elementWrapper.SetVectorIntRect("frames", component.frames);
        elementWrapper.SetStr("type", AnimationTypeEnum.ToString(component.animType));
        elementWrapper.SetBool("deleteOnDone", component.deleteOnDone);
    }
}
