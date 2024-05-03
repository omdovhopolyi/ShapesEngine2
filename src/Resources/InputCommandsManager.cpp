#include "InputCommandsManager.h"
#include "Commands/MoveCommands.h"
#include "Commands/RotateCommand.h"
#include "Commands/CameraMoveCommand.h"
#include "Commands/CameraZoomCommand.h"
#include "Serialization/Serialization.h"

#include <tinyxml2/tinyxml2.h>

namespace shen
{
    bool InputCommandsManager::Init()
    {
        RegisterLoaders();
        LoadFromXml();
        return true;
    }

    void InputCommandsManager::RegisterLoaders()
    {
        _loaders["MoveCommand"] = InputCommandsManager::LoadMoveCommand;
        _loaders["RotateCommand"] = InputCommandsManager::LoadRotateCommand;
        _loaders["CameraMoveCommand"] = InputCommandsManager::LoadCameraMoveCommand;
        _loaders["CameraZoomCommand"] = InputCommandsManager::LoadCameraZoomCommand;
    }

    void InputCommandsManager::LoadFromXml()
    {
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile("../assets/configs/commands.xml");
        if (error != tinyxml2::XML_SUCCESS)
        {
            // assert
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto element = elements->FirstChildElement("item");
            while (element)
            {
                const auto typeAttr = element->FindAttribute("type");
                const auto idAttr = element->FindAttribute("id");

                if (!typeAttr || !idAttr)
                {
                    // assert
                    continue;
                }

                const auto id = idAttr->Value();
                const auto type = typeAttr->Value();

                if (auto it = _loaders.find(type); it != _loaders.end())
                {
                    auto command = it->second(element);
                    command->SetType(type);
                    _assets[id] = std::move(command);
                }

                element = element->NextSiblingElement();
            }
        }
    }

    std::shared_ptr<Command> InputCommandsManager::LoadMoveCommand(const tinyxml2::XMLElement* element)
    {
        auto command = std::make_shared<MoveCommand>();

        if (const auto speedAttr = element->FindAttribute("speed"))
        {
            command->SetSpeed(speedAttr->FloatValue());
        }

        command->SetDirection(LoadVec2(element));

        return command;
    }

    std::shared_ptr<Command> InputCommandsManager::LoadRotateCommand(const tinyxml2::XMLElement* element)
    {
        return std::make_shared<RotateCommand>();
    }

    std::shared_ptr<Command> InputCommandsManager::LoadCameraMoveCommand(const tinyxml2::XMLElement* element)
    {
        auto command = std::make_shared<CameraMoveCommand>();

        if (const auto speedAttr = element->FindAttribute("speed"))
        {
            command->SetSpeed(speedAttr->FloatValue());
        }

        command->SetDirection(LoadVec2(element));

        return command;
    }

    std::shared_ptr<Command> InputCommandsManager::LoadCameraZoomCommand(const tinyxml2::XMLElement* element)
    {
        auto command = std::make_shared<CameraZoomCommand>();

        if (const auto speedAttr = element->FindAttribute("speed"))
        {
            command->SetSpeed(speedAttr->FloatValue());
        }

        return command;
    }
}
