#include "TestLoadSystem.h"
#include "ECS/SystemsManager.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
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
        auto elementWrapper = XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(FilePath::Path("assets/configs/test_load.xml"));
        Node root;
        LoadNode(root, elementWrapper);
    }

    void TestLoadSystem::LoadNode(Node& node, const DataElementWrapper& element)
    {
        element.ForAllChildren([&](const DataElementWrapper& childElement)
        {
            if (const auto type = childElement.GetStr("type"); !type.empty())
            {
                if (auto loader = LoadersManager::Instance().GetLoader(type))
                {
                    /*if (auto asset = loader->CreateAndLoad(childElement))
                    {
                        node.AddComponent(std::dynamic_pointer_cast<Component>(asset));
                    }*/
                }
            }
        });

        element.ForAllChildren("node", [&](const DataElementWrapper& nodeElement)
        {
            auto childNode = std::make_shared<Node>();
            LoadNode(*childNode, nodeElement);
            node.AddChild(childNode);
        });
    }
}
