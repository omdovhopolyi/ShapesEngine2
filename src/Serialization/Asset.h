#pragma once

#include <vector>
#include <memory>
#include <Serialization/SerializableField.h>

namespace shen
{
    class Asset
    {
    public:
        virtual ~Asset();

        template<class TField, class TVar>
        void RegisterVar(TVar& var, const std::string& name)
        {
            _fields.push_back(std::make_unique<TField>(var, name));
        }

        std::vector<std::unique_ptr<SerializableField>>& GetFields();

    protected:
        std::vector<std::unique_ptr<SerializableField>> _fields;
    };
}

