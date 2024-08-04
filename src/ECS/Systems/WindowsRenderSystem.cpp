#include "WindowsRenderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/WindowsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(WindowsRenderSystem)

    void WindowsRenderSystem::Draw()
    {
        auto renderTargets = _systems->GetSystem<SfmlRenderTargetsSystem>();
        auto windowsManager = _systems->GetSystem<WindowsManager>();

        if (renderTargets && windowsManager)
        {
            if (auto target = renderTargets->GetRenderTexture("ui"))
            {
                target->clear(sf::Color::Transparent);

                const auto& windows = windowsManager->GetWindows();

                for (const auto& window : windows)
                {
                    window->Draw();
                }

                target->display();
            }   
        }
    }
}
