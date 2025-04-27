#include "SystemsListLoader.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"

namespace shen
{
    bool SystemsListLoader::Load()
    {
        _systemsList.clear();

        auto elementWrapper = XmlDataElementWrapper{ nullptr };
        elementWrapper.LoadFile(FilePath::Path("assets/configs/systems.xml"));
        elementWrapper.ForAllChildren("system", [&](const DataElementWrapper& element)
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
