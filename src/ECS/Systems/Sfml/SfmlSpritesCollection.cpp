#include "SfmlSpritesCollection.h"
#include "tinyxml2/tinyxml2.h"
#include "Utils/Assert.h"
#include "Serialization/Serialization.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlSpritesCollection)

    void SfmlSpritesCollection::Start()
    {
        LoadSprites("../assets/configs/sprites.xml");
    }

    void SfmlSpritesCollection::Stop()
    {
        _sprites.clear();
    }

    void SfmlSpritesCollection::LoadSprites(const std::string& fileName)
    {
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile(fileName.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, "[SfmlSpritesCollection::LoadSprites] Can not read fonts path file");
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto textures = _systems->GetSystem<SfmlTexturesCollection>();

            auto element = elements->FirstChildElement("sprite");
            while (element)
            {
                const auto idAttr = element->FindAttribute("id");
                const auto texAttr = element->FindAttribute("tex");

                if (!idAttr)
                {
                    Assert(!idAttr, "[SfmlSpritesCollection::LoadSprites] No 'id' in sprites list");
                    continue;
                }

                if (!texAttr)
                {
                    Assert(!texAttr, "[SfmlSpritesCollection::LoadSprites] No 'tex' in sprites list");
                    continue;
                }

                const auto id = idAttr->Value();
                const auto textureId = texAttr->Value();
                const auto rect = Serialization::LoadIntRect(element);

                if (const auto texture = textures->GetTexture(textureId))
                {
                    _sprites[id] = sf::Sprite{ *texture, rect };
                }

                element = element->NextSiblingElement();
            }
        }
    }

    sf::Sprite SfmlSpritesCollection::GetSprite(const std::string& id)
    {
        if (auto it = _sprites.find(id); it != _sprites.end())
        {
            return it->second;
        }
        return {};
    }

    void SfmlSpritesCollection::RemoveSprite(const std::string& id)
    {
        _sprites.erase(id);
    }
}
