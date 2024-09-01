#include "SystemsListLoader.h"
#include "Serialization/Serialization.h"
#include "Utils/Assert.h"

namespace shen
{
    static std::string FileName = "../assets/configs/systems.xml";

    bool SystemsListLoader::Load()
    {
        _systemsList.clear();

        auto serialization = Serialization{ FileName };
        serialization.SetupElement("systems");
        serialization.ForAllChildElements("system", [&](const Serialization& element)
        {
            const auto systemType = element.GetStr("type");
            _systemsList.push_back(systemType);
        });

        return true;
    }

    const std::vector<std::string>& SystemsListLoader::GetSystemsList() const
    {
        return _systemsList;
    }
}
