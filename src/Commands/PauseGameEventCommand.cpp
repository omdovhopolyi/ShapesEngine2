#include "PauseGameEventCommand.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"

namespace shen
{
    REGISTER_LOADER(PauseGameEventCommand);

    void PauseGameEventCommand::Execute(const CommandContext& context) const
    {
        Messenger::Instance().Broadcast<PauseGameEvent>();
    }
}

