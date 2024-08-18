#pragma once

#include "InputCommandsLoadersCollection.h"
#include "Commands/Command.h"
#include "Serialization/Serialization.h"
#include "Registration/Registration.h"
#include <memory>

namespace shen
{
    class InputCommandLoader
    {
    public:
        InputCommandLoader();
        ~InputCommandLoader();

        virtual std::unique_ptr<Command> LoadCommand(Serialization& serialization) { return nullptr; }
    };
}
