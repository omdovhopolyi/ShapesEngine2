#include "CameraZoomCommandLoader.h"
#include "Commands/CameraZoomCommand.h"

namespace shen
{
    REGISTER_CLASS_LOADER(CameraZoomCommandLoader)

    std::unique_ptr<Command> CameraZoomCommandLoader::LoadCommand(Serialization& serialization)
    {
        auto command = std::make_unique<CameraZoomCommand>();
        command->SetSpeed(serialization.LoadFloatAttr("speed"));
        return command;
    }
}
