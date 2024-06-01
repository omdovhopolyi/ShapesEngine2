#include "SfmlUIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"

namespace shen
{
    void SfmlUIWindow::Update(float dt)
    {
        if (_root)
        {
            _root->Update(dt);
        }
    }

    void SfmlUIWindow::Draw()
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
}
