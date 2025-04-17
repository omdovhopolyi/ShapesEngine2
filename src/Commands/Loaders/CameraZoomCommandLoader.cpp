#include "CameraZoomCommandLoader.h"
#include "Commands/CameraZoomCommand.h"
#include "Serialization/DataElementWrapper.h"

namespace shen
{
    /*REGISTER_CLASS_LOADER(CameraZoomCommandLoader)

    std::unique_ptr<Command> CameraZoomCommandLoader::LoadCommand(const DataElementWrapper& elementWrapper)
    {
        auto command = std::make_unique<CameraZoomCommand>();
        LoadTypeAndId(elementWrapper, command.get());
        command->SetSpeed(elementWrapper.GetFloat("speed"));
        return command;
    }*/
}
