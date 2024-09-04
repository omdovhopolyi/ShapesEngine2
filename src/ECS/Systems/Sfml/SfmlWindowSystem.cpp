#include "SfmlWindowSystem.h"
#include "Serialization/Serialization.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlGameWindowSystem)

    void SfmlGameWindowSystem::Start()
    {
        auto serialization = Serialization{ "../assets/configs/window.xml" };
        serialization.SetupElement("window");
        _size = serialization.GetIntVec2("size", sf::Vector2i(800, 640));
        _name = serialization.GetStr("name");

        _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(_size.x, _size.y), _name);
    }

    void SfmlGameWindowSystem::Stop()
    {
        _window->close();
        _window = nullptr;
    }

    sf::RenderWindow* SfmlGameWindowSystem::GetWindow() const
    {
        return _window.get();
    }
}
