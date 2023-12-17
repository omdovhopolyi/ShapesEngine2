#pragma once

#include "AssetsManager.h"
#include "Texture.h"

namespace shen
{
    class OpenGLTexturesManager final
        : public AssetsManager<Texture*, std::shared_ptr<Texture>>
    {
    public:
        bool Init() override;

    protected:
        std::pair<std::shared_ptr<Texture>, bool> LoadAssetImpl(const std::string& path) override;

    private:
        void LoadFromXml();
        void CreateEmptyTexture();
    };
}
