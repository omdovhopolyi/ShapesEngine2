#include "SfmlWindowEndFrameSystem.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/SystemsManager.h"

namespace shen
{
    void SfmlWindowEndFrameSystem::Draw()
    {
        if (auto window = _systems->GetSystem<SfmlGameWindowSystem>())
        {
            if (auto sfmlWindow = window->GetRenderWindow())
            {
                sfmlWindow->display();
            }
        }
    }
}
