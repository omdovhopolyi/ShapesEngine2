#include "UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "ECS/Components/Common.h"
#include "UI/Components/UISpriteComponent.h"
#include "Utils/Assert.h"
#include <tinyxml2/tinyxml2.h>
#include <format>

namespace shen
{
    bool UIWindow::Init(const std::string& id, SystemsManager* systems)
    {
        _systems = systems;
        Assert(_systems, "Invalid ui window initialization");

        tinyxml2::XMLDocument doc;

        std::string path = "../assets/ui/" + id + ".xml";

        const auto error = doc.LoadFile(path.c_str());
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, std::format("[SfmlUIWindow::Init] Can not load window '{}'", id));
            return false;
        }

        _root = std::make_unique<UINode>();
        _root->SetWindow(this);

        if (auto rootElement = doc.FirstChildElement("root"))
        {
            LoadNode(_root.get(), rootElement);
        }

        return true;
    }

    void UIWindow::Update(float dt)
    {
        if (_root)
        {
            _root->Update(dt);
        }
    }

    void UIWindow::Draw()
    {
        if (_root)
        {
            if (auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>())
            {
                if (auto window = windowSystem->GetRenderWindow())
                {
                    _root->Draw(*window, {});
                }
            }
        }
    }

    void UIWindow::LoadNode(UINode* node, tinyxml2::XMLElement* element)
    {
        auto compElement = element->FirstChildElement("component");
        while (compElement)
        {
            if (const auto typeAttr = compElement->FindAttribute("type"))
            {
                const std::string type = typeAttr->Value();

                if (type == "sprite")
                {
                    auto component = node->AddComponent<UISpriteComponent>();

                    const auto fillScrAttr = compElement->FindAttribute("fillScreen");
                    const auto texAttr = compElement->FindAttribute("texture");

                    const bool needfillScreen = fillScrAttr->BoolValue();
                    const auto textureId = texAttr->Value();

                    auto textures = _systems->GetSystem<SfmlTexturesCollection>();
                    auto texture = textures->GetTexture(textureId);

                    component->SetTexture(texture);
                    component->SetFillScreen(needfillScreen);
                    component->SetNode(node);
                }
            }

            compElement = compElement->NextSiblingElement();
        }

        auto childNodeElement = element->FirstChildElement("node");
        while (childNodeElement)
        {
            auto child = node->AddChild("");
            child->SetWindow(this);

            LoadNode(child, childNodeElement);

            childNodeElement = childNodeElement->NextSiblingElement();
        }
    }
}
