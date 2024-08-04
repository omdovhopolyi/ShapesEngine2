#include "SfmlWindowBeginFrameSystem.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "ECS/SystemsManager.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlWindowBeginFrameSystem)

    void SfmlWindowBeginFrameSystem::Draw()
    {
        if (auto window = _systems->GetSystem<SfmlGameWindowSystem>())
        {
            if (auto sfmlWindow = window->GetRenderWindow())
            {
                sfmlWindow->clear(sf::Color::Black);
            }
        }
    }
}
