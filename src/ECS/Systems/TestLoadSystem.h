#pragma once

#include "BaseSystems/System.h"
#include "UI/Components/TestComponent.h"

namespace shen
{
    class Serialization;
    class Node;

    class TestLoadSystem
        : public System
    {
        SYSTEMS_FACTORY(TestLoadSystem)

    public:
        void Load() override;
        void LoadNode(Node& node, const Serialization& serialization);
    };
}
