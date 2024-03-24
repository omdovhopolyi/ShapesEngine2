#pragma once

#include "AssetsManager.h"
#include "Commands/Command.h"
#include <functional>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class InputCommandsManager final
        : public AssetsManager<std::shared_ptr<Command>, std::shared_ptr<Command>>
    {
    public:
        bool Init() override;

    private:
        void RegisterLoaders();
        void LoadFromXml();

        static std::shared_ptr<Command> LoadMoveCommand(const tinyxml2::XMLElement* element);
        static std::shared_ptr<Command> LoadRotateCommand(const tinyxml2::XMLElement* element);
        static std::shared_ptr<Command> LoadCameraMoveCommand(const tinyxml2::XMLElement* element);

    private:
        std::map<std::string, std::function<std::shared_ptr<Command>(const tinyxml2::XMLElement* element)>> _loaders;
    };
}
