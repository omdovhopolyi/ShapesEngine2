#include "Physics.h"
#include "ECS/EcsWorld.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void RigidBody::Load(Entity entity, EcsWorld* world, const tinyxml2::XMLElement* element)
    {
        auto comp = world->AddComponent<RigidBody>(entity);

        comp->type = LoadInt("type", element);
        comp->size = LoadVec2("size", element, comp->size);
        comp->sensor = LoadBool("sensor", element, comp->sensor);
    }

    void RigidBody::Save(Entity entity, EcsWorld* world, tinyxml2::XMLElement* element)
    {

    }
}
