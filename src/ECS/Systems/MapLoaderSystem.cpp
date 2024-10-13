#include "MapLoaderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "ECS/World.h"
#include "Utils/Assert.h"

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

    void MapLoaderSystem::LoadMap(const std::string& mapId)
    {
        auto& world = _systems->GetWorld();

        auto serialization = Serialization{ _systems, "../assets/configs/maps/" + mapId + ".xml" };
        serialization.SetupElement("items");
        serialization.ForAllChildElements("entity", [&](const Serialization& element)
        {
            auto entity = world.CreateEntity();

            element.ForAllChildElements("component", [&](const Serialization& componentElement)
            {
                if (const auto type = componentElement.GetStr("type"); !type.empty())
                {
                    if (auto it = _functions.find(type); it != _functions.end())
                    {
                        it->second.loadFunc(entity, componentElement);
                    }
                }
            });
        });
    }
}
