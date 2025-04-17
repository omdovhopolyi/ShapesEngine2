#include "MoveCommandLoader.h"
#include "Commands/MoveCommands.h"
#include "Serialization/DataElementWrapper.h"

namespace shen
{
    /*REGISTER_CLASS_LOADER(MoveCommandLoader)

    std::unique_ptr<Command> MoveCommandLoader::LoadCommand(const DataElementWrapper& elementWrapper)
    {
        auto command = std::make_unique<MoveCommand>();
        LoadTypeAndId(elementWrapper, command.get());
        command->SetSpeed(elementWrapper.GetFloat("speed"));
        command->SetDirection(elementWrapper.GetVec2("direction"));
        return command;
    }*/
}
