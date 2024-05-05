#include "MapLoaderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "ECS/World.h"

namespace shen
{
    void MapLoaderSystem::Init(SystemsManager* systems)
    {
        System::Init(systems);

        // TODO subscriptions
    }

    void MapLoaderSystem::Start()
    {
        LoadMap("map_test");
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
        RegisterLoader<Mover>("mover");
    }

    void MapLoaderSystem::LoadMap(const std::string& mapId)
    {
        tinyxml2::XMLDocument doc;

        std::string filePath = "../assets/configs/maps/" + mapId + ".xml";

        const auto error = doc.LoadFile(filePath.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            // assert
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto& world = _systems->GetWorld();

            auto elementEntity = elements->FirstChildElement("entity");
            while (elementEntity)
            {
                auto entity = world.CreateEntity();

                auto elementComponent = elementEntity->FirstChildElement("component");
                while (elementComponent)
                {
                    if (const auto typeAttr = elementComponent->FindAttribute("type"))
                    {
                        const auto type = typeAttr->Value();

                        if (auto it = _functions.find(type); it != _functions.end())
                        {
                            it->second.loadFunc(entity, elementComponent);
                        }
                    }

                    elementComponent = elementComponent->NextSiblingElement();
                }

                elementEntity = elementEntity->NextSiblingElement();
            }
        }
    }
}
