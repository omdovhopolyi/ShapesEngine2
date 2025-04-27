#include "PausePhysicsAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "Serialization/Types/SerializableFieldBool.h"

namespace shen
{
    PausePhisicsAction::PausePhisicsAction(bool pause/* = true*/)
        : ActionBase()
        , _pause(pause)
    {}

    void PausePhisicsAction::RegisterProperties()
    {
        RegisterVar<SerializableFieldBool>(_pause, "pause");
    }

    void PausePhisicsAction::Execute(const ContextBase& context) const
    {
        if (auto physics = context.systems->GetSystem<PhysicsBox2DSystem>())
        {
            physics->Pause(_pause);
        }
    }
}
