#include "CameraZoomCommandLoader.h"
#include "Commands/CameraZoomCommand.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_CLASS_LOADER(CameraZoomCommandLoader)

    std::unique_ptr<Command> CameraZoomCommandLoader::LoadCommand(const Serialization& serialization)
    {
        auto command = std::make_unique<CameraZoomCommand>();
        LoadTypeAndId(serialization, command.get());
        command->SetSpeed(serialization.GetFloat("speed"));
        return command;
    }
}
