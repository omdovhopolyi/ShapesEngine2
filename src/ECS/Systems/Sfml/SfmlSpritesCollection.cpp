#include "SfmlSpritesCollection.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Serialization/Serialization.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlSpritesCollection)

    void SfmlSpritesCollection::Start()
    {
        LoadSprites(FilePath::Path("assets/configs/sprites.xml"));
    }

    void SfmlSpritesCollection::Stop()
    {
        _sprites.clear();
    }

    void SfmlSpritesCollection::LoadSprites(const std::string& fileName)
    {
        auto textures = _systems->GetSystem<SfmlTexturesCollection>();

        auto serialization = Serialization{ _systems, fileName };
        serialization.SetupElement("items");
        serialization.ForAllChildElements("sprite", [&](const Serialization& element)
        {
            const auto id = element.GetStr("id");
            const auto textureId = element.GetStr("tex");
            const auto rect = element.GetIntRect("rect");
            
            if (const auto texture = textures->GetTexture(textureId))
            {
                _sprites[id] = sf::Sprite{ *texture, rect };
            }
        });
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
