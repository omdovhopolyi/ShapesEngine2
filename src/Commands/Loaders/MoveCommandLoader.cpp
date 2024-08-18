#include "MoveCommandLoader.h"
#include "Commands/MoveCommands.h"

namespace shen
{
    REGISTER_CLASS_LOADER(MoveCommandLoader)

    std::unique_ptr<Command> MoveCommandLoader::LoadCommand(Serialization& serialization)
    {
        auto command = std::make_unique<MoveCommand>();
        command->SetSpeed(serialization.LoadFloatAttr("speed"));

        sf::Vector2f direction;
        direction.x = serialization.LoadFloatAttr("x");
        direction.y = serialization.LoadFloatAttr("y");

        command->SetDirection(direction);

        return command;
    }
}
