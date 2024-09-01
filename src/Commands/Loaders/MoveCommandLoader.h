#pragma once

#include "InputCommandLoader.h"

namespace shen
{
    class MoveCommand;

    class MoveCommandLoader
        : public InputCommandLoader
    {
        CLASS_LOADER(InputCommandsLoadersCollection, MoveCommand)

    public:
        std::unique_ptr<Command> LoadCommand(const Serialization& serialization) override;
    };
}
