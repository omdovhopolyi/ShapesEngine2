#pragma once

#include "BaseSystems/System.h"
#include "Commands/Command.h"
#include <tinyxml2/tinyxml2.h>
#include <functional>
#include <memory>
#include <map>

namespace shen
{
    class Serialization;

    class InputCommandsCollection
        : public System
    {
    public:
        using LoaderFunc = std::function<std::unique_ptr<Command>(Serialization&)>;

        void Init(SystemsManager* systems) override;
        void Start() override;
        void Stop() override;

        Command* GetCommandById(const std::string& commandId) const;

    private:
        void RegisterLoaders();
        void LoadFromXml();
        void ClearCommands();

        static std::unique_ptr<Command> LoadMoveCommand(Serialization& serialization);
        static std::unique_ptr<Command> LoadRotateCommand(Serialization& serialization);
        static std::unique_ptr<Command> LoadCameraMoveCommand(Serialization& serialization);
        static std::unique_ptr<Command> LoadCameraZoomCommand(Serialization& serialization);

    private:
        std::map<std::string, LoaderFunc> _loaders;
        std::map<std::string, std::unique_ptr<Command>> _commands;
    };
}
