#pragma once

#include <vector>
#include <memory>
#include <typeindex>
#include "SerializableField.h"
#include "SerializableMacro.h"

namespace shen
{
    class Serializable
    {
    public:
        virtual ~Serializable();

        virtual void RegisterProperties() {}

        template<class TField, class TVar, class... Args>
        void RegisterVar(TVar& var, const std::string& name, Args... args)
        {
            _fields.push_back(std::make_unique<TField>(var, name, std::forward<Args>(args)...));
        }

        std::vector<std::unique_ptr<SerializableField>>& GetFields();

        virtual std::string GetTypeName() const { return {}; }
        virtual std::type_index GetTypeIndex() const { return std::type_index(typeid(Serializable)); };

        void Save(DataElementWrapper& element);
        void Load(const DataElementWrapper& element);

        virtual void AfterLoad() {}
        virtual void BeforeSave() {}

    protected:
        std::vector<std::unique_ptr<SerializableField>> _fields;
    };
}

