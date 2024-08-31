#include "CameraMoveCommandLoader.h"
#include "Commands/CameraMoveCommand.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_CLASS_LOADER(CameraMoveCommandLoader)

    std::unique_ptr<Command> CameraMoveCommandLoader::LoadCommand(const Serialization& serialization)
    {
        auto command = std::make_unique<CameraMoveCommand>();
        LoadTypeAndId(serialization, command.get());
        command->SetSpeed(serialization.GetFloat("speed"));
        command->SetDirection(serialization.GetVec2("direction"));
        return command;
    }
}
