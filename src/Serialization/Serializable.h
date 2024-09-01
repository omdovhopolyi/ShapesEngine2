#pragma once

#include <map>
#include <string>
#include <any>
#include <functional>

namespace shen
{
    class Serialization;

    class Value {};

    template<class T>
    class BaseValue
        : public Value
    {
    public:
        virtual void SetValue(const T& value)
        {
            _value = value;
        }
        
        virtual const T& GetValue() const
        {
            return _value;
        }

    protected:
        T _value = {};
    };

    class BoolValue : public BaseValue<bool> {};
    class IntValue : public BaseValue<int> {};
    class FloatValue : public BaseValue<float> {};

    class Serializable
    {
    public:
        virtual void Load(Serialization& serialization) {}
        virtual void Save(Serialization& serialization) {}

    protected:
        std::map<std::string, Value*> _variables;
    };
}
