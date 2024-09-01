#pragma once

#include "InputCommandsLoadersCollection.h"
#include "Registration/Registration.h"
#include "Commands/Command.h"
#include <memory>

namespace shen
{
    class Serialization;

    class InputCommandLoader
    {
    public:
        void LoadTypeAndId(const Serialization& serialization, Command* command);

        virtual std::unique_ptr<Command> LoadCommand(const Serialization& serialization) { return nullptr; }
    };
}
