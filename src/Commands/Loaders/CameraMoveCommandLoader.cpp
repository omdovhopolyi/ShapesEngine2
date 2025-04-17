#include "CameraMoveCommandLoader.h"
#include "Commands/CameraMoveCommand.h"
#include "Serialization/DataElementWrapper.h"

namespace shen
{
    /*REGISTER_CLASS_LOADER(CameraMoveCommandLoader)

    std::unique_ptr<Command> CameraMoveCommandLoader::LoadCommand(const DataElementWrapper& elementWrapper)
    {
        auto command = std::make_unique<CameraMoveCommand>();
        LoadTypeAndId(elementWrapper, command.get());
        command->SetSpeed(elementWrapper.GetFloat("speed"));
        command->SetDirection(elementWrapper.GetVec2("direction"));
        return command;
    }*/
}
