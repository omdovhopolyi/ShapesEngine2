#include "PauseGameEventCommand.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

namespace shen
{
    void PauseGameEventCommand::Execute(const CommandContext& context) const
    {
        Messenger::Instance().Broadcast<PauseGameEvent>();
    }
}

