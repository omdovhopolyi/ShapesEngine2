#pragma once

#include <vector>
#include <memory>
#include "Serialization/Serializable.h"

// TODO delete

namespace shen
{
    class Component
        : public Serializable
    {
    };

    class UITestComponent
        : public Component
    {
        SERIALIZABLE(UITestComponent)

    public:
        void RegisterProperties() override;

    private:

    private:
        int _intVal = 0;
        float _floatVal = 0.f;
        std::string _stringVal;
        std::shared_ptr<UITestComponent> _componentVal;
    };
}
