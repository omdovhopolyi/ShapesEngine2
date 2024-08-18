#include "RotateCommandLoader.h"
#include "Commands/RotateCommand.h"

namespace shen
{
    REGISTER_CLASS_LOADER(RotateCommandLoader)

    std::unique_ptr<Command> RotateCommandLoader::LoadCommand(Serialization& serialization)
    {
        return std::make_unique<RotateCommand>();
    }
}
