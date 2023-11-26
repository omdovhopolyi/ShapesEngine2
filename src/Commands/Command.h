#pragma once

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

        virtual void Execute(const Entity& entity, const CommandContext& context = {}) const = 0;
    };
}
