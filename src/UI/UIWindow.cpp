#include "UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "ECS/Components/Common.h"
#include "UI/Components/UISpriteComponent.h"
#include "Utils/Assert.h"
#include "Messenger/Events/UIEvents.h"
#include <format>

namespace shen
{
    bool UIWindow::Init(const std::string& id, SystemsManager* systems)
    {
        _systems = systems;
        _id = id;
        Assert(_systems, "Invalid ui window initialization");
        return true;
    }

    void UIWindow::Update(float dt)
    {
        if (IsComponentsDirty())
        {
            RemoveExpiredComponents();
            SetupInputComponentsArray();
            SetComponentsDirty(false);
        }

        if (_root)
        {
            _root->Update(dt);
        }
    }

    void UIWindow::Draw()
    {
        if (_root)
        {
            if (auto renderTargets = _systems->GetSystem<SfmlRenderTargetsSystem>())
            {
                if (auto target = renderTargets->GetRenderTexture("ui"))
                {
                    _root->Draw(*target, {});
                }
            }
        }
    }

    const std::string& UIWindow::GetId() const
    {
        return _id;
    }

    const std::shared_ptr<UINode>& UIWindow::GetOrCreateRoot()
    {
        if (_root)
        {
            return _root;
        }
        
        _root = std::make_shared<UINode>();
        _root->SetWindow(this);
        _root->SetName("root");

        return _root;
    }

    void UIWindow::MapComponent(const std::string& id, const std::shared_ptr<UIComponent>& component)
    {
        const auto [it, isInserted] = _mappedComponents.insert({ id, component });
        SetComponentsDirty(true);
        Assert(isInserted, std::format("Trying add second component for node '{}' in window '{}'", id, GetId()));
    }

    void UIWindow::MapInputComponent(const std::string& id, const std::shared_ptr<UIInputComponent>& component)
    {
        const auto [it, isInserted] = _mappedInputComponents.insert({ id, component });
        SetComponentsDirty(true);
        Assert(isInserted, std::format("Trying add second input component for node '{}' in window '{}'", id, GetId()));
    }

    void UIWindow::MapNode(const std::string& id, const std::shared_ptr<UINode>& node)
    {
        const auto [it, isInserted] = _mappedNodes.insert({ id, node });
        Assert(isInserted, std::format("Trying map second node '{}' in window '{}'", id, GetId()));
    }

    void UIWindow::SetComponentsDirty(bool dirty)
    {
        _componentsDirty = dirty;
    }

    bool UIWindow::IsComponentsDirty() const
    {
        return _componentsDirty;
    }

    void UIWindow::ResolveReferences()
    {
        for (auto& [id, weakComponent] : _mappedComponents)
        {
            if (auto component = weakComponent.lock())
            {
                component->ResolveReferences();
            }
        }
    }

    void UIWindow::InitComponents()
    {
        InitComponentsForNode(_root.get());
    }

    std::weak_ptr<UIComponent> UIWindow::GetComponent(const std::string& id) const
    {
        if (auto it = _mappedComponents.find(id); it != _mappedComponents.end())
        {
            return it->second;
        }

        return {};
    }

    std::weak_ptr<UIInputComponent> UIWindow::GetInputComponent(const std::string& id) const
    {
        if (auto it = _mappedInputComponents.find(id); it != _mappedInputComponents.end())
        {
            return it->second;
        }

        return {};
    }

    std::weak_ptr<UINode> UIWindow::GetNode(const std::string& id) const
    {
        if (auto it = _mappedNodes.find(id); it != _mappedNodes.end())
        {
            return it->second;
        }

        return {};
    }

    bool UIWindow::ProcessInput(const InputType& inputType, const CommandContext& context)
    {
        for (const auto& component : _inputComponents)
        {
            return component->ProcessInput(inputType, context);
        }

        return false;
    }

    void UIWindow::InitSubscriptions()
    {
        _subscriptions.Subscribe<InputComponentsDirty>([&](const InputComponentsDirty& event)
        {
            if (event.windowId == GetId())
            {
                SetComponentsDirty(true);
            }
        });
    }

    template<class Comp>
    void RemoveExpiredComponentsFor(std::map<std::string, std::weak_ptr<Comp>>& container)
    {
        for (auto it = container.begin(); it != container.end();)
        {
            if (it->second.expired())
            {
                it = container.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    void UIWindow::RemoveExpiredComponents()
    {
        RemoveExpiredComponentsFor(_mappedComponents);
        RemoveExpiredComponentsFor(_mappedInputComponents);
    }

    void UIWindow::SetupInputComponentsArray()
    {
        _inputComponents.clear();

        for (const auto& [nodeName, weakComponent] : _mappedInputComponents)
        {
            if (const auto& component = weakComponent.lock())
            {
                _inputComponents.push_back(component.get());
            }
        }

        std::sort(_inputComponents.begin(), _inputComponents.end(), [](const auto& left, const auto& right)
        {
            return left->GetInputPriority() < right->GetInputPriority();
        });
    }

    void UIWindow::InitComponentsForNode(UINode* node)
    {
        for (auto& [typeId, component] : node->GetComponents())
        {
            component->Init();
        }

        for (auto& child : node->GetChildren())
        {
            InitComponentsForNode(child.get());
        }
    }
}
