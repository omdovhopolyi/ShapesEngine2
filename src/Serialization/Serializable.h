#pragma once

#include <vector>
#include <memory>
#include <typeindex>
#include <Serialization/SerializableField.h>

namespace shen
{
    class Serializable
    {
    public:
        virtual ~Serializable();

        virtual void RegisterProperties() {}

        template<class TField, class TVar>
        void RegisterVar(TVar& var, const std::string& name = {})
        {
            _fields.push_back(std::make_unique<TField>(var, name));
        }

        std::vector<std::unique_ptr<SerializableField>>& GetFields();

        //virtual std::string& GetTypeName() const = 0;
        //virtual std::type_index GetTypeIndex() const = 0;

        void Save(DataElementWrapper& element);
        void Load(const DataElementWrapper& element);

        virtual void AfterLoad() {}
        virtual void BeforeSave() {}

    protected:
        std::vector<std::unique_ptr<SerializableField>> _fields;
    };
}

