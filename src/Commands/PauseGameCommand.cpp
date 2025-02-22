#include "PauseGameCommand.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"

namespace shen
{
    void PauseGameCommand::Execute(const CommandContext& context) const
    {
        auto& time = context.systems->GetTime();
        const bool isPaused = time.IsGamePaused();
        time.PauseGame(!isPaused);
    }
}
