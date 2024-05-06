#include "InputCommandsCollection.h"
#include "Serialization/Serialization.h"
#include "Commands/MoveCommands.h"
#include "Commands/RotateCommand.h"
#include "Commands/CameraMoveCommand.h"
#include "Commands/CameraZoomCommand.h"
#include "Utils/Assert.h"

namespace shen
{
    void InputCommandsCollection::Init(SystemsManager* systems)
    {
        RegisterLoaders();
    }

    void InputCommandsCollection::Start()
    {
        LoadFromXml();
    }

    void InputCommandsCollection::Stop()
    {
        ClearCommands();
    }

    Command* InputCommandsCollection::GetCommandById(const std::string& commandId) const
    {
        if (auto it = _commands.find(commandId); it != _commands.end())
        {
            return it->second.get();
        }

        return nullptr;
    }

    void InputCommandsCollection::RegisterLoaders()
    {
        _loaders["MoveCommand"] = InputCommandsCollection::LoadMoveCommand;
        _loaders["RotateCommand"] = InputCommandsCollection::LoadRotateCommand;
        _loaders["CameraMoveCommand"] = InputCommandsCollection::LoadCameraMoveCommand;
        _loaders["CameraZoomCommand"] = InputCommandsCollection::LoadCameraZoomCommand;
    }

    void InputCommandsCollection::LoadFromXml()
    {
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile("../assets/configs/commands.xml");
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, "[InputCommandsCollection::LoadFromXml] Can not read commands.xml");
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto element = elements->FirstChildElement("item");
            while (element)
            {
                const auto typeAttr = element->FindAttribute("type");
                const auto idAttr = element->FindAttribute("id");

                if (!typeAttr)
                {
                    Assert(!typeAttr, "[InputCommandsCollection::LoadFromXml] No 'type' attribute in command");
                    continue;
                }

                if (!idAttr)
                {
                    Assert(!idAttr, "[InputCommandsCollection::LoadFromXml] No 'id' attribute in command");
                    continue;
                }

                const auto id = idAttr->Value();
                const auto type = typeAttr->Value();

                if (auto it = _loaders.find(type); it != _loaders.end())
                {
                    auto serialization = Serialization(_systems, element);

                    auto command = it->second(serialization);
                    command->SetType(type);
                    _commands[id] = std::move(command);
                }

                element = element->NextSiblingElement();
            }
        }
    }

    void InputCommandsCollection::ClearCommands()
    {
        _loaders.clear();
        _commands.clear();
    }

    std::unique_ptr<Command> InputCommandsCollection::LoadMoveCommand(Serialization& serialization)
    {
        auto command = std::make_unique<MoveCommand>();
        command->SetSpeed(serialization.LoadFloat("speed"));

        sf::Vector2f direction;
        direction.x = serialization.LoadFloat("x");
        direction.y = serialization.LoadFloat("y");

        command->SetDirection(direction);

        return command;
    }

    std::unique_ptr<Command> InputCommandsCollection::LoadRotateCommand(Serialization& serialization)
    {
        return std::make_unique<RotateCommand>();
    }

    std::unique_ptr<Command> InputCommandsCollection::LoadCameraMoveCommand(Serialization& serialization)
    {
        auto command = std::make_unique<CameraMoveCommand>();
        command->SetSpeed(serialization.LoadFloat("speed"));

        sf::Vector2f direction;
        direction.x = serialization.LoadFloat("x");
        direction.y = serialization.LoadFloat("y");

        command->SetDirection(direction);

        return command;
    }

    std::unique_ptr<Command> InputCommandsCollection::LoadCameraZoomCommand(Serialization& serialization)
    {
        auto command = std::make_unique<CameraZoomCommand>();
        command->SetSpeed(serialization.LoadFloat("speed"));
        return command;
    }
}
