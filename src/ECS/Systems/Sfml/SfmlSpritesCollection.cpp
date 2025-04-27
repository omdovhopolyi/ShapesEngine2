#include "SfmlSpritesCollection.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
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

        auto elementWrapper = XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(fileName);
        elementWrapper.ForAllChildren("sprite", [&](const DataElementWrapper& element)
        {
            const auto id = element.GetStr("id");
            const auto textureId = element.GetStr("tex");
            const auto rect = element.GetIntRect("rect");
            const auto anchor = element.GetVec2("anchor");
            
            if (const auto texture = textures->GetTexture(textureId))
            {
                auto sprite = sf::Sprite{ *texture, rect };
                sprite.setOrigin(anchor);
                _sprites[id] = { sprite, textureId };
            }
        });
    }

    sf::Sprite SfmlSpritesCollection::GetSprite(const std::string& id) const
    {
        const auto& spriteData = GetSpriteData(id);
        return spriteData.sprite;
    }

    const SfmlSpriteData& SfmlSpritesCollection::GetSpriteData(const std::string& id) const
    {
        if (auto it = _sprites.find(id); it != _sprites.end())
        {
            return it->second;
        }

        static SfmlSpriteData empty;
        return empty;
    }

    const std::string SfmlSpritesCollection::GetSpritesTexId(const std::string& id) const
    {
        const auto& spriteData = GetSpriteData(id);
        return spriteData.textureId;
    }

    void SfmlSpritesCollection::RemoveSprite(const std::string& id)
    {
        _sprites.erase(id);
    }
}
