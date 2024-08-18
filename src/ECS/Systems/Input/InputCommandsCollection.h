#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <tinyxml2/tinyxml2.h>
#include <functional>
#include <memory>
#include <map>

namespace shen
{
    class Command;
    class Serialization;

    class InputCommandsCollection
        : public System
    {
        SYSTEMS_FACTORY(InputCommandsCollection)

    public:
        void Start() override;
        void Stop() override;

        Command* GetCommandById(const std::string& commandId) const;

    private:
        void LoadFromXml();
        void ClearCommands();

    private:
        std::map<std::string, std::unique_ptr<Command>> _commands;
    };
}
