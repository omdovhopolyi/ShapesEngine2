#include "SfmlWindowSystem.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
#include "Utils/FilePath.h"
#include <SFML/Window/WindowStyle.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(SfmlGameWindowSystem)

    void SfmlGameWindowSystem::Start()
    {
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

    sf::Vector2i SfmlGameWindowSystem::GetSize()
    {
        if (_window)
        {
            return static_cast<sf::Vector2i>(_window->getSize());
        }

        return {};
    }

    void SfmlGameWindowSystem::Load()
    {
        auto elementWrapper = XmlDataElementWrapper{ GetSystems() };
        elementWrapper.LoadFile(FilePath::Path("assets/configs/window.xml"));
        _size = elementWrapper.GetIntVec2("size", sf::Vector2i(800, 640));
        _name = elementWrapper.GetStr("name");
        _titlebar = elementWrapper.GetBool("titlebar", true);
        _resize = elementWrapper.GetBool("resize", true);
        _close = elementWrapper.GetBool("close", true);
        _fullscreen = elementWrapper.GetBool("fullscreen", false);
    }

    void SfmlGameWindowSystem::CreateSFMLWindow(unsigned int flags)
    {
        _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(_size.x, _size.y), _name, flags);
    }
}
