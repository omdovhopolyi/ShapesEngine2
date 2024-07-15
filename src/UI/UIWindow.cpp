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

    UINode* UIWindow::GetOrCreateRoot()
    {
        if (_root)
        {
            return _root.get();
        }
        
        _root = std::make_unique<UINode>();
        _root->SetWindow(this);
        _root->SetName("root");

        return _root.get();
    }

    void UIWindow::AddInputComponent(const std::string& nodeName, const std::shared_ptr<UIInputComponent>& component)
    {
        const auto [it, isInserted] = _mappedInputComponents.insert({ nodeName, component });

        if (isInserted)
        {
            SetInputComponentsDirty(true);
        }
        else
        {
            Assert(false, std::format("Trying add second input component for node '{}' in window '{}'", nodeName, GetId()));
        }
    }

    void UIWindow::RemoveInputComponents(const std::string& nodeName)
    {
        _mappedInputComponents.erase(nodeName);
        SetInputComponentsDirty(true);
    }

    void UIWindow::SetInputComponentsDirty(bool dirty)
    {
        _inputComponentsDirty = dirty;
    }

    bool UIWindow::IsInputComponentsDirty() const
    {
        return _inputComponentsDirty;
    }

    bool UIWindow::ProcessInput(const InputType& inputType, const CommandContext& context)
    {
        if (IsInputComponentsDirty())
        {
            SetupComponentsArray();
            SetInputComponentsDirty(false);
        }

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
                SetInputComponentsDirty(true);
            }
        });
    }

    void UIWindow::SetupComponentsArray()
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
}
