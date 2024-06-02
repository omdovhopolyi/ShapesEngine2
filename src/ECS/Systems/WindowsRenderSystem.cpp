#include "WindowsRenderSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/WindowsManager.h"

namespace shen
{
    void WindowsRenderSystem::Draw()
    {
        if (auto windowsManager = _systems->GetSystem<WindowsManager>())
        {
            const auto& windows = windowsManager->GetWindows();

            for (const auto& window : windows)
            {
                window->Draw();
            }
        }
    }
}
