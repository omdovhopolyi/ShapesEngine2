#include "SerializableFieldSprite.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"

namespace shen
{
    SerializableFieldSprite::SerializableFieldSprite(sf::Sprite& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    { }

    void SerializableFieldSprite::Load(const DataElementWrapper& element)
    {
        if (auto systems = element.GetSystems())
        {
            if (const auto spritesCollection = systems->GetSystem<SfmlSpritesCollection>())
            {
                if (const auto spriteElement = element.GetChildElement(_name)) {
                    const auto spriteId = spriteElement->GetStr("spriteId");
                    _field = spritesCollection->GetSprite(spriteId);
                }
            }
        }
    }
}
