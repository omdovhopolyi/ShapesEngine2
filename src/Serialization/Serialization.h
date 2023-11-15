#pragma once

#include "Utils/Types.h"
#include <glm/glm.hpp>
#include <tinyxml2/tinyxml2.h>
#include <string>
#include <vector>

namespace shen
{
    class Texture;

    int LoadInt(const std::string& id, const tinyxml2::XMLElement* element, int defaultVal = 0);
    float LoadFloat(const std::string& id, const tinyxml2::XMLElement* element, float defaultVal = 0.f);
    std::string LoadStr(const std::string& id, const tinyxml2::XMLElement* element, const std::string& defaultVal = {});

    glm::vec2 LoadVec2(const std::string& id, const tinyxml2::XMLElement* element, glm::vec2 defaultVal = glm::vec2(0.f));
    glm::vec3 LoadVec3(const std::string& id, const tinyxml2::XMLElement* element, glm::vec3 defaultVal = glm::vec3(0.f));
    
    Rect LoadRect(const std::string& id, const tinyxml2::XMLElement* element, Rect def = {});
    Rect LoadRect(const tinyxml2::XMLElement* element);

    glm::vec4 LoadColor(const std::string& id, const tinyxml2::XMLElement* element, glm::vec4 defaultVal = glm::vec4(0.f));

    Texture* LoadTexturePtr(const std::string& id, const tinyxml2::XMLElement* elemnt);
    std::vector<Rect> LoadVectorRect(const std::string& id, const tinyxml2::XMLElement* element);
}
