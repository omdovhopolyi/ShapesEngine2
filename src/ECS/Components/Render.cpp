#include "Render.h"
#include "Game/GameFacade.h"
#include "ECS/World.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "ECS/SystemsManager.h"
#include "Serialization/DataElementWrapper.h"
#include "Serialization/Types/SerializableFieldString.h"
#include "Serialization/Types/SerializableFieldIntRect.h"
#include "Serialization/Types/SerializableFieldVec2.h"
#include "Serialization/Types/SerializableFieldInt.h"
#include "Serialization/Types/SerializableFieldBool.h"
#include "Serialization/Types/SerializableFieldColor.h"
#include "Serialization/Types/SerializableFieldFloat.h"
#include "Serialization/Types/SerializableFieldListIntRect.h"
#include "Utils/Math.h"

namespace shen
{
    REGISTER_LOADER(Sprite)

    void Sprite::RegisterProperties()
    {
        RegisterVar<SerializableFieldString>(textureId, "texture");
        RegisterVar<SerializableFieldIntRect>(rect, "rect");
        RegisterVar<SerializableFieldVec2>(anchor, "anchor");
        RegisterVar<SerializableFieldInt>(sorting, "sorting");
        RegisterVar<SerializableFieldBool>(autoRect, "autoRect");
        RegisterVar<SerializableFieldBool>(autoAnchor, "autoAnchor");
    }

    void Sprite::AfterLoad()
    {
        if (auto systems = GameFacade::GetSystemsManager())
        {
            if (auto texturesCollection = systems->GetSystem<SfmlTexturesCollection>())
            {
                if (auto texture = texturesCollection->GetTexture(textureId))
                {
                    sprite.setTexture(*texture);
                    
                    auto textureSize = texture->getSize();

                    if (autoRect)
                    {
                        auto texRect = sf::IntRect{ 0, 0, static_cast<int>(textureSize.x), static_cast<int>(textureSize.y) };
                        sprite.setTextureRect(texRect);
                    }
                    else
                    {
                        sprite.setTextureRect(rect);
                    }

                    if (autoAnchor)
                    {
                        auto textMidAnchor = sf::Vector2f{ textureSize.x / 2.f, textureSize.y / 2.f };
                        sprite.setOrigin(textMidAnchor);
                    }
                    else
                    {
                        sprite.setOrigin(anchor);
                    }
                }
            }
        }
    }

    REGISTER_LOADER(Color)

    void Color::RegisterProperties()
    {
        RegisterVar<SerializableFieldColor>(color, "color");
    }

    REGISTER_LOADER(SpriteFrameAnimation)

    void SpriteFrameAnimation::RegisterProperties()
    {
        RegisterVar<SerializableFieldFloat>(frameTime, "frameTime");
        RegisterVar<SerializableFieldListIntRect>(frames, "frames", "rect");
        RegisterVar<SerializableFieldString>(animTypeStr, "animType");
        RegisterVar<SerializableFieldBool>(deleteOnDone, "deleteOnDone");
    }

    void SpriteFrameAnimation::AfterLoad()
    {
        animType = AnimationTypeEnum.FromString(animTypeStr);
    }
}
