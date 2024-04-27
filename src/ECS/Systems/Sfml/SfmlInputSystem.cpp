#include "SfmlInputSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace shen
{
	void SfmlInputSystem::Update()
	{

		auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>();
		auto window = windowSystem->GetWindow();

		sf::Event event;

		bool alt = (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt));
		bool shift = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift));
		bool ctrl = (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl));

		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				Messenger::Instance().Broadcast<Quit>();
				break;
			}
			case sf::Event::KeyPressed:
			{
				Messenger::Instance().Broadcast<KeyEvent>(
					InputEventType::Down, 
					event.key.code, 
					event.key.alt, 
					event.key.shift, 
					event.key.control
				);

				break;
			}
			case sf::Event::KeyReleased:
			{
				Messenger::Instance().Broadcast<KeyEvent>(
					InputEventType::Up, 
					event.key.code, 
					event.key.alt, 
					event.key.shift, 
					event.key.control
				);

				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				Messenger::Instance().Broadcast<MouseButtonEvent>(
					InputEventType::Down,
					static_cast<MouseButton>(event.mouseButton.button),		
					event.mouseButton.x,
					event.mouseButton.y,
					alt,
					shift,
					ctrl
				);

				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				Messenger::Instance().Broadcast<MouseButtonEvent>(
					InputEventType::Up,
					static_cast<MouseButton>(event.mouseButton.button),
					event.mouseButton.x,
					event.mouseButton.y,
					alt,
					shift,
					ctrl
				);

				break;
			}
			case sf::Event::MouseMoved:
			{
				int xrel = 0;
				int yrel = 0;

				if (_lastMouseXPos >= 0 && _lastMouseYPos >= 0)
				{
					xrel = event.mouseMove.x - _lastMouseXPos;
					yrel = event.mouseMove.y - _lastMouseYPos;
				}

				Messenger::Instance().Broadcast<MouseMoveEvent>(
					event.mouseMove.x,
					event.mouseMove.y,
					xrel,
					yrel,
					alt,
					shift,
					ctrl
				);

				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				Messenger::Instance().Broadcast<MouseWheelEvent>(
					event.mouseWheel.x,
					event.mouseWheel.y,
					event.mouseWheel.delta,
					alt,
					shift,
					ctrl
				);

				break;
			}
			default:
				break;
			}
		}

		for (auto key = 0; key < static_cast<int>(sf::Keyboard::Key::KeyCount); key++)
		{
			bool keyPressed = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
			if (keyPressed)
			{
				Messenger::Instance().Broadcast<KeyEvent>(InputEventType::Hold, key, alt, shift, ctrl);
			}
		}

		sf::Vector2i localPosition = sf::Mouse::getPosition(*window);

		for (auto mouseBtn = 0; mouseBtn < static_cast<int>(sf::Mouse::Button::ButtonCount); mouseBtn++)
		{
			bool btnPressed = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(mouseBtn));
			if (btnPressed)
			{
				Messenger::Instance().Broadcast<MouseButtonEvent>(
					InputEventType::Hold,
					static_cast<MouseButton>(mouseBtn),
					localPosition.x,
					localPosition.y,
					alt,
					shift,
					ctrl
				);
			}
		}
	}
}
