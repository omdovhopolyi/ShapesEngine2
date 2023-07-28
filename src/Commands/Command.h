#pragma once

namespace shen
{
    class Entity;

    class Command
    {
    public:
        virtual ~Command() = default;

        virtual void Execute(const Entity& entity) const = 0;
    };
}
