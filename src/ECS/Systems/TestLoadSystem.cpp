#include "TestLoadSystem.h"
#include "ECS/SystemsManager.h"
#include "Serialization/Serialization.h"
#include "Utils/FilePath.h"
#include "Utils/Assert.h"
#include "UI/Node.h"
#include "UI/Components/TestComponent.h"
#include "Serialization/LoadersManager.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(TestLoadSystem);

    void TestLoadSystem::Load()
    {
        auto element = Serialization{ _systems, FilePath::Path("assets/configs/test_load.xml") };
        element.SetupFirstElement();
        Node root;
        LoadNode(root, element);
    }

    void TestLoadSystem::LoadNode(Node& node, const Serialization& serialization)
    {
        serialization.ForAllChildren([&](const Serialization& element)
        {
            if (const auto type = element.GetStr("type"); !type.empty())
            {
                if (auto loader = LoadersManager::Instance().GetLoader(type))
                {
                    if (auto asset = loader->CreateAndLoad(element))
                    {
                        node.AddComponent(std::dynamic_pointer_cast<Component>(asset));
                    }
                }
            }
        });

        serialization.ForAllChildElements("node", [&](const Serialization& nodeElement)
        {
            auto childNode = std::make_shared<Node>();
            LoadNode(*childNode, nodeElement);
            node.AddChild(childNode);
        });
    }
}
