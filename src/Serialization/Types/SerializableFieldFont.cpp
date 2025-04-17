#include "SerializableFieldFont.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlFontsCollection.h"

namespace shen
{
    SerializableFieldFont::SerializableFieldFont(sf::Font& field, const std::string& name)
        : SerializableField(name)
        , _field(field)
    {
    }

    void SerializableFieldFont::Load(const DataElementWrapper& element)
    {
        if (auto systems = element.GetSystems())
        {
            const auto fontId = element.GetStr(_name);
            if (auto fonts = systems->GetSystem<SfmlFontsCollection>())
            {
                if (auto font = fonts->GetFont(fontId))
                {
                    _field = *font;
                }
            }
        }
    }
}
