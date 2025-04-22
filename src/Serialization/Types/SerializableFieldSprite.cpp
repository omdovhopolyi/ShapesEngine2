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
                const auto spriteId = element.GetStr(_name);
                _field = spritesCollection->GetSprite(spriteId);
            }
        }
    }
}
