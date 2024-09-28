#include "SfmlWindowSystem.h"
#include "Serialization/Serialization.h"
#include <SFML/Window/WindowStyle.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlGameWindowSystem)

    void SfmlGameWindowSystem::Start()
    {
        Load();
        auto flags = GetWindowFlags();
        CreateSFMLWindow(flags);
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

    unsigned int SfmlGameWindowSystem::GetWindowFlags() const
    {
        auto flags = static_cast<unsigned int>(sf::Style::None);
        flags |= static_cast<unsigned int>(_titlebar ? sf::Style::Titlebar : sf::Style::None);
        flags |= static_cast<unsigned int>(_resize ? sf::Style::Resize : sf::Style::None);
        flags |= static_cast<unsigned int>(_close ? sf::Style::Close : sf::Style::None);
        flags |= static_cast<unsigned int>(_fullscreen ? sf::Style::Fullscreen : sf::Style::None);
        
        return flags;
    }

    void SfmlGameWindowSystem::Load()
    {
        auto serialization = Serialization{ "../assets/configs/window.xml" };
        serialization.SetupElement("window");
        _size = serialization.GetIntVec2("size", sf::Vector2i(800, 640));
        _name = serialization.GetStr("name");
        _titlebar = serialization.GetBool("titlebar", true);
        _resize = serialization.GetBool("resize", true);
        _close = serialization.GetBool("close", true);
        _fullscreen = serialization.GetBool("fullscreen", false);
    }

    void SfmlGameWindowSystem::CreateSFMLWindow(unsigned int flags)
    {
        _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(_size.x, _size.y), _name, flags);
    }
}
