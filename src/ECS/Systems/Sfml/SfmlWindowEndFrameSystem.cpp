#include "SfmlWindowEndFrameSystem.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/SystemsManager.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlWindowEndFrameSystem)

    void SfmlWindowEndFrameSystem::Draw()
    {
        if (auto window = _systems->GetSystem<SfmlGameWindowSystem>())
        {
            if (auto sfmlWindow = window->GetWindow())
            {
                sfmlWindow->display();
            }
        }
    }
}
