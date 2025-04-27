#include "MapLoaderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "ECS/Systems/ObjectsAssetsCollectonSystem.h"
//#include "ECS/World.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(MapLoaderSystem)

    void MapLoaderSystem::Init(SystemsManager* systems)
    {
        System::Init(systems);
        RegisterLoaders();
        // TODO subscriptions
    }

    void MapLoaderSystem::RegisterLoaders()
    {
        RegisterLoader<Sprite>("sprite");
        RegisterLoader<Camera>("camera");
        RegisterLoader<Transform>("transform");
        RegisterLoader<SpriteFrameAnimation>("spriteFrameAnimation");
        RegisterLoader<Color>("color");
        RegisterLoader<PlayerInput>("playerInput");
        RegisterLoader<RigidBody>("rigidBody");
    }

    void MapLoaderSystem::LoadMap(const std::string& mapId) const
    {
        auto elementWrapper = XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(FilePath::Path("assets/configs/maps/") + mapId + ".xml");
        LoadMap(elementWrapper, mapId);
    }

    void MapLoaderSystem::LoadMap(DataElementWrapper& element, const std::string& mapId) const
    {
        element.ForAllChildren("entity", [&](const DataElementWrapper& child)
        {
            CreateEntityAndLoadComponents(child);
        });

        shen::Messenger::Instance().Broadcast<MapLoadedEvent>(mapId);
    }

    void MapLoaderSystem::LoadComponents(Entity entity, const DataElementWrapper& element) const
    {
        element.ForAllChildren("component", [&](const DataElementWrapper& componentElement)
        {
            if (const auto type = componentElement.GetStr("type"); !type.empty())
            {
                if (auto it = _functions.find(type); it != _functions.end())
                {
                    it->second.loadFunc(entity, componentElement);
                }
            }
        });
    }

    Entity MapLoaderSystem::CreateEntityAndLoadComponents(const DataElementWrapper& element) const
    {
        auto& world = _systems->GetWorld();
        auto entity = world.CreateEntity();
        InstantiateAsset(entity, element);
        LoadComponents(entity, element);
        return entity;
    }

    Entity MapLoaderSystem::InstantiateAsset(const std::string& assetId) const
    {
        if (auto assetsCollection = _systems->GetSystem<ObjectsAssetsCollectonSystem>())
        {
            if (const auto assetData = assetsCollection->GetData(assetId))
            {
                return CreateEntityAndLoadComponents(*assetData);
            }
        }

        return {};
    }

    void MapLoaderSystem::InstantiateAsset(Entity entity, const DataElementWrapper& element) const
    {
        element.ForAllChildren("asset", [&](const DataElementWrapper& childElement)
        {
            if (const auto id = childElement.GetStr("id"); !id.empty())
            {
                InstantiateAsset(id);
            }
        });
    }
}
