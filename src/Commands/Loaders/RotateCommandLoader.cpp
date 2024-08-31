#include "RotateCommandLoader.h"
#include "Commands/RotateCommand.h"

namespace shen
{
    REGISTER_CLASS_LOADER(RotateCommandLoader)

    std::unique_ptr<Command> RotateCommandLoader::LoadCommand(const Serialization& serialization)
    {
        auto command = std::make_unique<RotateCommand>();
        LoadTypeAndId(serialization, command.get());
        return command;
    }
}
