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

        void SetId(const std::string& id) { _id = id; }
        const std::string& GetId() const { return _id; }

        virtual void Execute(const CommandContext& context = {}) const = 0;

    protected:
        std::string _id;
        std::string _type;
    };
}
