#include "UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Systems/Sfml/SfmlTexturesCollection.h"
#include "ECS/Components/Common.h"
#include "UI/Components/UISpriteComponent.h"
#include "Utils/Assert.h"
#include <format>

namespace shen
{
    bool UIWindow::Init(const std::string& id, SystemsManager* systems)
    {
        _systems = systems;
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
}
