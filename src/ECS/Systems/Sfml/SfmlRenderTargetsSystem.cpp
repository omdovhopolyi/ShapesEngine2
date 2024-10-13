#include "SfmlRenderTargetsSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include <optional>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlRenderTargetsSystem)

    std::string SfmlRenderTargetsSystem::WorldTargetId = "World";
    std::string SfmlRenderTargetsSystem::UITargetId = "UI";

    void SfmlRenderTargetsSystem::Start()
    {
        if (const auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>())
        {
            const auto windowSize = static_cast<sf::Vector2f>(windowSystem->GetSize());

            CreateTexture(WorldTargetId, windowSize);
            CreateTexture(UITargetId, windowSize);
        }
    }

    void SfmlRenderTargetsSystem::Draw()
    {
        auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>();
        auto window = windowSystem->GetWindow();

        for (const auto& texData : _renderTextures)
        {
            const auto& texture = texData->texture.getTexture();
            window->draw(sf::Sprite(texture));
        }
    }

    void SfmlRenderTargetsSystem::CreateTexture(const std::string& id, sf::Vector2f size)
    {
        auto renderTextureData = std::make_unique<RenderTextureData>();
        renderTextureData->id = id;
        renderTextureData->texture.create(size.x, size.y);
        _mappedTextures[id] = &renderTextureData->texture;
        _renderTextures.push_back(std::move(renderTextureData));
    }

    sf::RenderTexture* SfmlRenderTargetsSystem::GetRenderTexture(const std::string& id)
    {
        if (auto it = _mappedTextures.find(id); it != _mappedTextures.end())
        {
            return it->second;
        }

        return nullptr;
    }
}
