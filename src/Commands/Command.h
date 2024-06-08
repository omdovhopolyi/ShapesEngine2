#pragma once

#include "CommandContext.h"

namespace shen
{
    class Entity;

    class Command
    {
    public:
        virtual ~Command() = default;

        void SetType(const std::string& type) { _type = type; }
        const std::string& GetType() const { return _type; }

        virtual void Execute(const CommandContext& context = {}) const = 0;

    protected:
        std::string _type;
    };
}
