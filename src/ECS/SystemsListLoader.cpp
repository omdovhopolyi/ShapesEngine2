#include "SystemsListLoader.h"
#include "Serialization/Serialization.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"

namespace shen
{
    bool SystemsListLoader::Load()
    {
        _systemsList.clear();

        auto serialization = Serialization{ FilePath::Path("assets/configs/systems.xml") };
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
