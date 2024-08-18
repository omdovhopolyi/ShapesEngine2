#pragma once

#include "InputCommandLoader.h"

namespace shen
{
    class RotateCommand;

    class RotateCommandLoader
        : public InputCommandLoader
    {
        CLASS_LOADER(InputCommandsLoadersCollection, RotateCommand)

    public:
        std::unique_ptr<Command> LoadCommand(Serialization& serialization) override;
    };
}
