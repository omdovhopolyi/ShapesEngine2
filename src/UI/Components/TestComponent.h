#pragma once

#include <vector>
#include <memory>
#include "Serialization/Asset.h"
#include "Serialization/LoaderMacro.h"

namespace shen
{
    class Component
        : public Asset
    {
    };

    class UITestComponent
        : public Component
    {
        CLASS_LOADER_TEST(UITestComponent)

    public:
        UITestComponent();

    private:

    private:
        int _intVal = 0;
        float _floatVal = 0.f;
        std::string _stringVal;
        std::shared_ptr<UITestComponent> _componentVal;
    };
}
