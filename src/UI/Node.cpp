#include "Node.h"

namespace shen
{
    void Node::AddChild(const std::shared_ptr<Node>& child)
    {
        _children.push_back(child);
    }

    void Node::AddComponent(const std::shared_ptr<Component>& comp)
    {
        _components.push_back(comp);
    }
}
