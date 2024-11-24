#include "ObjectsAssetsCollectonSystem.h"
#include "Utils/FilePath.h"
#include "Utils/Assert.h"
#include <format>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(ObjectsAssetsCollectonSystem)

    void ObjectsAssetsCollectonSystem::Load()
    {
        LoadObjects();
    }

    const Serialization& ObjectsAssetsCollectonSystem::GetData(const std::string& assetId) const
    {
        if (auto it = _assets.find(assetId); it != _assets.end())
        {
            return it->second;
        }

        Assert(false, std::format("[ObjectsAssetsCollectonSystem::GetData] No asset data '{}'", assetId));
        static Serialization empty;
        return empty;
    }

    void ObjectsAssetsCollectonSystem::LoadObjects()
    {
        const auto filePath = FilePath::Path("assets/objects/objects.xml");

        auto serialization = Serialization{ _systems, filePath };
        serialization.SetupElement("objects");
        serialization.ForAllChildElements("object", [&](const Serialization& objectData)
        {
            const auto id = objectData.GetStr("id");
            const auto path = FilePath::Path(objectData.GetStr("path"));

            const auto [it, isInserted] = _assets.insert({ id, Serialization{ _systems, path } });
            if (isInserted)
            {
                it->second.SetupElement("object");
            }
            else
            {
                Assert(false, std::format("[ObjectsAssetsCollectonSystem::LoadObjects] Can not read file '{}'", path));
            }
        });

    }
}
