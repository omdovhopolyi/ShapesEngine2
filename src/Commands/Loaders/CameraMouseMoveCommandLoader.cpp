#include "CameraMouseMoveCommandLoader.h"
#include "Commands/CameraMouseMoveCommand.h"

namespace shen
{
    REGISTER_CLASS_LOADER(CameraMouseMoveCommandLoader)

    std::unique_ptr<Command> CameraMouseMoveCommandLoader::LoadCommand(Serialization& serialization)
    {
        return std::make_unique<CameraMouseMoveCommand>();
    }
}
