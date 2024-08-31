#pragma once

#include "InputCommandLoader.h"

namespace shen
{
    class CameraZoomCommand;

    class CameraZoomCommandLoader
        : public InputCommandLoader
    {
        CLASS_LOADER(InputCommandsLoadersCollection, CameraZoomCommand)

    public:
        std::unique_ptr<Command> LoadCommand(const Serialization& serialization) override;
    };
}
