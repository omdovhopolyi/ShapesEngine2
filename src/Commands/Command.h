#pragma once

#include <string>

namespace shen
{
    class Entity;

    struct CommandContext
    {
        int x = 0;
        int y = 0;
    };

    class Command
    {
    public:
        virtual ~Command() = default;

        void SetType(const std::string& type) { _type = type; }
        const std::string& GetType() const { return _type; }

        virtual void Execute(const Entity& entity, const CommandContext& context = {}) const = 0;

    protected:
        std::string _type;
    };
}
