#pragma once

#include <vector>
#include <memory>
#include "UI/Components/TestComponent.h"

namespace shen
{
    class Node
    {
    public:
        void AddChild(const std::shared_ptr<Node>& child);
        void AddComponent(const std::shared_ptr<Component>& comp);

    private:
        std::vector<std::shared_ptr<Node>> _children;
        std::vector<std::shared_ptr<Component>> _components;
    };
}
