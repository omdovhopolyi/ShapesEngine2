#include "CameraMouseMoveCommandLoader.h"
#include "Commands/CameraMouseMoveCommand.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_CLASS_LOADER(CameraMouseMoveCommandLoader)

    std::unique_ptr<Command> CameraMouseMoveCommandLoader::LoadCommand(const Serialization& serialization)
    {
        auto command = std::make_unique<CameraMouseMoveCommand>();
        LoadTypeAndId(serialization, command.get());
        return command;
    }
}
