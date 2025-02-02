#include "ResetPhysicsAccumulatedTimeAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"

namespace shen
{
    void ResetPhisicsAccumulatedTimeAction::Execute(const shen::ContextBase& context) const
    {
        if (auto physics = context.systems->GetSystem<PhysicsBox2DSystem>())
        {
            physics->ResetAccumulatedTime();
        }
    }
}
