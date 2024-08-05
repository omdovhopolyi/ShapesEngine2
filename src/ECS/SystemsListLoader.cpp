#include "SystemsListLoader.h"
#include "Utils/Assert.h"

namespace shen
{
    static std::string FileName = "../assets/configs/systems.xml";

    bool SystemsListLoader::Load()
    {
        _systemsList.clear();

        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile(FileName.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, "[SystemsListLoader::Load] Can not read systems list file");
            return false;
        }

        if (auto elements = doc.FirstChildElement("systems"))
        {
            auto element = elements->FirstChildElement("system");
            while (element)
            {
                if (const auto typeAttr = element->FindAttribute("type"))
                {
                    const auto type = typeAttr->Value();

                    _systemsList.push_back(type);
                }

                element = element->NextSiblingElement();
            }
        }

        return true;
    }

    const std::vector<std::string>& SystemsListLoader::GetSystemsList() const
    {
        return _systemsList;
    }
}
