#include "OpenGLTexturesManager.h"

#include "Logger/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>

namespace shen
{
    std::pair<std::shared_ptr<Texture>, bool> OpenGLTexturesManager::LoadAssetImpl(const std::string& path)
    {
        unsigned int textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        int width = 0;
        int height = 0;
        int nrChannels = 0;

        if (unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0))
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
}
