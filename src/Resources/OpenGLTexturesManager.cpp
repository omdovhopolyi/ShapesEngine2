#include "OpenGLTexturesManager.h"

#include "Logger/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    bool OpenGLTexturesManager::Init()
    {
        stbi_set_flip_vertically_on_load(true);
        LoadFromXml();
        CreateEmptyTexture();
        return true;
    }

    std::pair<std::shared_ptr<Texture>, bool> OpenGLTexturesManager::LoadAssetImpl(const std::string& path)
    {
        unsigned int textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        int width = 0;
        int height = 0;
        int nrChannels = 0;

        if (unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0))
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height , 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(data);

            auto tex = std::make_shared<Texture>();
            tex->SetId(textureId);
            tex->SetPath(path);
            tex->SetSize({ width, height });

            return { std::move(tex), true };
        }
        else
        {
            Logger::Log("Failed to load texture: {}", path);
        }

        return { nullptr, false };
    }

    void OpenGLTexturesManager::LoadFromXml()
    {
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile("../assets/configs/textures.xml");
        if (error != tinyxml2::XML_SUCCESS)
        {
            // assert
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto element = elements->FirstChildElement("item");
            while (element)
            {
                const auto idAttr = element->FindAttribute("id");
                const auto pathAttr = element->FindAttribute("path");

                if (!idAttr || !pathAttr)
                {
                    // assert
                    continue;
                }

                const auto id = idAttr->Value();
                const auto path = pathAttr->Value();

                LoadAsset(id, path);

                element = element->NextSiblingElement();
            }
        }
    }

    void OpenGLTexturesManager::CreateEmptyTexture()
    {
        unsigned int textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned char data[] = { 0 };

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        auto tex = std::make_shared<Texture>();
        tex->SetId(textureId);
        tex->SetSize({ 1, 1 });

        _assets["Empty"] = std::move(std::move(tex));
    }
}
