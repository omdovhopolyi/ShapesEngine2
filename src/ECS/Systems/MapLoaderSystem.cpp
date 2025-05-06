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
#include "Serialization/LoadersManager.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(MapLoaderSystem)

    void MapLoaderSystem::Init(SystemsManager* systems)
    {
        System::Init(systems);
        //RegisterLoaders();
        // TODO subscriptions
    }

    void MapLoaderSystem::RegisterLoaders()
    {
        /*RegisterLoader<Sprite>("sprite");
        RegisterLoader<Camera>("camera");
        RegisterLoader<Transform>("transform");
        RegisterLoader<SpriteFrameAnimation>("spriteFrameAnimation");
        RegisterLoader<Color>("color");
        RegisterLoader<PlayerInput>("playerInput");
        RegisterLoader<RigidBody>("rigidBody");*/
    }

    void MapLoaderSystem::LoadMap(const std::string& mapId)
    {
        auto elementWrapper = XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(FilePath::Path("assets/configs/maps/") + mapId + ".xml");
        LoadMap(elementWrapper, mapId);
    }

    void MapLoaderSystem::LoadMap(DataElementWrapper& element, const std::string& mapId)
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
                if (auto loader = LoadersManager::Instance().GetLoader(type))
                {
                    loader->CreateAndLoad(componentElement);
                }

                /*if (auto it = _functions.find(type); it != _functions.end())
                {
                    it->second.loadFunc(entity, componentElement);
                }*/
            }
        });
    }

    Entity MapLoaderSystem::CreateEntityAndLoadComponents(const DataElementWrapper& element)
    {
        auto& world = _systems->GetWorld();
        auto entity = world.CreateEntity();
        SetCurrentLoadingEntity(entity);
        InstantiateAsset(entity, element);
        LoadComponents(entity, element);
        ResetCurrentLoadingEntity();
        return entity;
    }

    Entity MapLoaderSystem::InstantiateAsset(const std::string& assetId)
    {
        if (assetId == "hit_1")
        {
            bool check = true;
        }

        if (auto assetsCollection = _systems->GetSystem<ObjectsAssetsCollectonSystem>())
        {
            if (const auto assetData = assetsCollection->GetData(assetId))
            {
                return CreateEntityAndLoadComponents(*assetData);
            }
        }

        return {};
    }

    Entity MapLoaderSystem::GetCurrentLoadingEntity() const
    {
        return _currentLoadingEntity;
    }

    void MapLoaderSystem::ResetCurrentLoadingEntity()
    {
        _currentLoadingEntity = {};
    }

    void MapLoaderSystem::SetCurrentLoadingEntity(Entity entity)
    {
        _currentLoadingEntity = entity;
    }

    void MapLoaderSystem::InstantiateAsset(Entity entity, const DataElementWrapper& element)
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
