#include "ObjectsAssetsCollectonSystem.h"
#include "Utils/FilePath.h"
#include "Utils/Assert.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
#include <format>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(ObjectsAssetsCollectonSystem)

    void ObjectsAssetsCollectonSystem::Load()
    {
        LoadObjects();
    }

    const DataElementWrapper* ObjectsAssetsCollectonSystem::GetData(const std::string& assetId) const
    {
        if (auto it = _assets.find(assetId); it != _assets.end())
        {
            return it->second.get();
        }

        Assert(false, std::format("[ObjectsAssetsCollectonSystem::GetData] No asset data '{}'", assetId));
        return nullptr;
    }

    void ObjectsAssetsCollectonSystem::LoadObjects()
    {
        auto elementWrapper = XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(FilePath::Path("assets/objects/objects.xml"));
        elementWrapper.ForAllChildren("object", [&](const DataElementWrapper& childElement)
        {
            const auto id = childElement.GetStr("id");
            const auto path = FilePath::Path(childElement.GetStr("path"));

            const auto [it, isInserted] = _assets.insert({ id, std::make_unique<XmlDataElementWrapper>(_systems) });
            Assert(isInserted, std::format("[ObjectsAssetsCollectonSystem::LoadObjects] Can not read file '{}'", path));
            it->second->LoadFile(path);
        });
    }
}
