#include "MoveCommandLoader.h"
#include "Commands/MoveCommands.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_CLASS_LOADER(MoveCommandLoader)

    std::unique_ptr<Command> MoveCommandLoader::LoadCommand(const Serialization& serialization)
    {
        auto command = std::make_unique<MoveCommand>();
        LoadTypeAndId(serialization, command.get());
        command->SetSpeed(serialization.GetFloat("speed"));
        command->SetDirection(serialization.GetVec2("direction"));
        return command;
    }
}
