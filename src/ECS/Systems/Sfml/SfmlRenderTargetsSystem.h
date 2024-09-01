#pragma once

#include "ECS/Systems/BaseSystems/RenderSystem.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <map>
#include <vector>
#include <memory>

namespace shen
{
    struct RenderTextureData
    {
        std::string id;
        sf::RenderTexture texture;
    };

    class SfmlRenderTargetsSystem
        : public RenderSystem
    {
        SYSTEMS_FACTORY(SfmlRenderTargetsSystem)

    public:
        static std::string WorldTargetId;
        static std::string UITargetId;

        void Start() override;
        void Draw() override;

        void CreateTexture(const std::string& id, sf::Vector2f size);

        sf::RenderTexture* GetRenderTexture(const std::string& id);

    private:
        std::vector<std::unique_ptr<RenderTextureData>> _renderTextures;
        std::map<std::string, sf::RenderTexture*> _mappedTextures;
    };
}
