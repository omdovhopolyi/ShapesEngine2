#include "MapLoaderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "ECS/World.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include "ECS/Systems/ObjectsAssetsCollectonSystem.h"

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
        auto serialization = Serialization{ _systems, FilePath::Path("assets/configs/maps/") + mapId + ".xml" };
        LoadMap(serialization, mapId);
    }

    void MapLoaderSystem::LoadMap(Serialization& serialization, const std::string& mapId) const
    {
        serialization.SetupElement("items");
        serialization.ForAllChildElements("entity", [&](const Serialization& element)
        {
            CreateEntityAndLoadComponents(element);
        });

        shen::Messenger::Instance().Broadcast<MapLoadedEvent>(mapId);
    }

    void MapLoaderSystem::LoadComponents(Entity entity, const Serialization& serialization) const
    {
        serialization.ForAllChildElements("component", [&](const Serialization& componentElement)
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

    Entity MapLoaderSystem::CreateEntityAndLoadComponents(const Serialization& serialization) const
    {
        auto& world = _systems->GetWorld();
        auto entity = world.CreateEntity();
        InstantiateAsset(entity, serialization);
        LoadComponents(entity, serialization);
        return entity;
    }

    Entity MapLoaderSystem::InstantiateAsset(const std::string& assetId) const
    {
        if (auto assetsCollection = _systems->GetSystem<ObjectsAssetsCollectonSystem>())
        {
            const auto& assetData = assetsCollection->GetData(assetId);
            return CreateEntityAndLoadComponents(assetData);
        }

        return {};
    }

    void MapLoaderSystem::InstantiateAsset(Entity entity, const Serialization& serialization) const
    {
        serialization.ForAllChildElements("asset", [&](const Serialization& assetElement)
        {
            if (const auto id = assetElement.GetStr("id"); !id.empty())
            {
                InstantiateAsset(id);
            }
        });
    }
}
