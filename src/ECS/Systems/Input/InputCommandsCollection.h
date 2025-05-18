#pragma once

#include "ECS/Systems/BaseSystems/System.h"
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

        void AddCommand(const std::string& id, const std::shared_ptr<Command>& command);

    private:
        void LoadFromXml();
        void ClearCommands();

    private:
        std::map<std::string, std::shared_ptr<Command>> _commands;
    };
}
