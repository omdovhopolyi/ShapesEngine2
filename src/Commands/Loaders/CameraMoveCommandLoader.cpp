#include "CameraMoveCommandLoader.h"
#include "Commands/CameraMoveCommand.h"

namespace shen
{
    REGISTER_CLASS_LOADER(CameraMoveCommandLoader)

    std::unique_ptr<Command> CameraMoveCommandLoader::LoadCommand(Serialization& serialization)
    {
        auto command = std::make_unique<CameraMoveCommand>();
        command->SetSpeed(serialization.LoadFloatAttr("speed"));

        sf::Vector2f direction;
        direction.x = serialization.LoadFloatAttr("x");
        direction.y = serialization.LoadFloatAttr("y");

        command->SetDirection(direction);

        return command;
    }
}
