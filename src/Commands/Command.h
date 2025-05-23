#pragma once

#include "CommandContext.h"
#include "Serialization/Serializable.h"

namespace shen
{
    class Command
        : public Serializable
    {
    public:
        virtual ~Command() = default;

        void RegisterProperties() override;

        void SetType(const std::string& type) { _type = type; }
        const std::string& GetType() const { return _type; }

        void SetId(const std::string& id) { _id = id; }
        const std::string& GetId() const { return _id; }

        void SetGlobal(bool global) { _isGlobal = global; }
        bool IsGlobal() const { return _isGlobal; }

        virtual void Execute(const CommandContext& context = {}) const = 0;

    protected:
        std::string _id;
        std::string _type;
        bool _isGlobal = false;
    };
}
