#pragma once

#include "BaseSystems/System.h"

namespace shen
{
    class DataElementWrapper;
    class Node;

    class TestLoadSystem
        : public System
    {
        SYSTEMS_FACTORY(TestLoadSystem)

    public:
        void Load() override;
        void LoadNode(Node& node, const DataElementWrapper& element);
    };
}
