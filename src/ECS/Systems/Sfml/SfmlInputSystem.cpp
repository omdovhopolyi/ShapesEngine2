#include "SfmlInputSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlWindowSystem.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Common.h"
#include "Utils/Assert.h"
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>

namespace shen
{
	REGISTER_SYSTEMS_FACTORY(SfmlInputSystem)

	void SfmlInputSystem::Start()
	{
		GenerateCharKeyMap();
		GenerateKeyCharMap();
	}

	void SfmlInputSystem::Update()
	{
		auto windowSystem = _systems->GetSystem<SfmlGameWindowSystem>();
		auto window = windowSystem->GetWindow();

		sf::Event event;

		bool alt = (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt));
		bool shift = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift));
		bool ctrl = (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl));

		std::vector<sf::Mouse::Button> pressedMouseButtons;

		for (auto mouseBtn = 0; mouseBtn < static_cast<int>(sf::Mouse::Button::ButtonCount); mouseBtn++)
		{
			bool btnPressed = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(mouseBtn));
			if (btnPressed)
			{
				pressedMouseButtons.push_back(static_cast<sf::Mouse::Button>(mouseBtn));
			}
		}

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

				_lastMouseXPos = event.mouseMove.x;
				_lastMouseYPos = event.mouseMove.y;

				MouseButton button = (pressedMouseButtons.empty() ? MouseButton::None : static_cast<MouseButton>(pressedMouseButtons.front()));

				Messenger::Instance().Broadcast<MouseMoveEvent>(
					button,
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
					event.mouseWheelScroll.x,
					event.mouseWheelScroll.y,
					event.mouseWheelScroll.delta,
					alt,
					shift,
					ctrl
				);

				break;
			}
			case sf::Event::LostFocus:
			{
				Messenger::Instance().Broadcast<LostFocus>();
				break;
			}
			case sf::Event::GainedFocus:
			{
				Messenger::Instance().Broadcast<GainedFocus>();
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

		auto localPosition = sf::Mouse::getPosition(*window);

		for (auto mouseBtn : pressedMouseButtons)
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

	bool SfmlInputSystem::IsKeyPressed(sf::Keyboard::Key key) const
	{
		return sf::Keyboard::isKeyPressed(key);
	}

	bool SfmlInputSystem::IsMouseButtonPressed(sf::Mouse::Button button) const
	{
		return sf::Mouse::isButtonPressed(button);
	}

	std::string SfmlInputSystem::GetCharByKey(sf::Keyboard::Key key) const
	{
		if (auto it = _keyCharMap.find(key); it != _keyCharMap.end())
		{
			return it->second;
		}
		return "";
	}

	sf::Keyboard::Key SfmlInputSystem::GetKeyByChar(const std::string& charKeyStr, bool silent/* = false*/) const
	{
		if (!charKeyStr.empty())
		{
			if (auto it = _charKeyMap.find(charKeyStr); it != _charKeyMap.end())
			{
				return it->second;
			}
		}
		
		if (!silent)
		{
			Assert(false, "[SfmlInputSystem::GetKeyByChar] Empty char key string");
		}
		
		return sf::Keyboard::Unknown;
	}

	void SfmlInputSystem::GenerateCharKeyMap()
	{
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			_charKeyMap[{ c }] = static_cast<sf::Keyboard::Key>(c - 'A');
		}

		for (char c = 'a'; c <= 'z'; ++c)
		{
			_charKeyMap[{ c }] = static_cast<sf::Keyboard::Key>(c - 'a');
		}

		for (char c = '0'; c <= '9'; ++c)
		{
			_charKeyMap[{ c }] = static_cast<sf::Keyboard::Key>(sf::Keyboard::Num0 + (c - '0'));
		}

		_charKeyMap["Esc"] = sf::Keyboard::Escape;
		_charKeyMap[{ ' ' }] = sf::Keyboard::Space;
		_charKeyMap[{ '\t' }] = sf::Keyboard::Tab;
		_charKeyMap[{ '\n' }] = sf::Keyboard::Return;
		_charKeyMap[{ ',' }] = sf::Keyboard::Comma;
		_charKeyMap[{ '.' }] = sf::Keyboard::Period;
		_charKeyMap[{ '/' }] = sf::Keyboard::Slash;
		_charKeyMap[{ '\\' }] = sf::Keyboard::Backslash;
		_charKeyMap[{ '\'' }] = sf::Keyboard::Quote;
		_charKeyMap[{ ';' }] = sf::Keyboard::SemiColon;
		_charKeyMap[{ '[' }] = sf::Keyboard::LBracket;
		_charKeyMap[{ ']' }] = sf::Keyboard::RBracket;
		_charKeyMap[{ '-' }] = sf::Keyboard::Dash;
		_charKeyMap[{ '=' }] = sf::Keyboard::Equal;
		_charKeyMap[{ '`' }] = sf::Keyboard::Tilde;
		_charKeyMap["Left"] = sf::Keyboard::Left;
		_charKeyMap["Right"] = sf::Keyboard::Right;
		_charKeyMap["Up"] = sf::Keyboard::Up;
		_charKeyMap["Down"] = sf::Keyboard::Down;

		for (int i = 1; i <= 24; ++i)
		{
			char key = 'F' + i - 1;
			_charKeyMap[{ key }] = static_cast<sf::Keyboard::Key>(sf::Keyboard::F1 + i - 1);
		}
	}

	void SfmlInputSystem::GenerateKeyCharMap()
	{
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			_keyCharMap[static_cast<sf::Keyboard::Key>(c - 'A')] = c;
		}

		for (char c = '0'; c <= '9'; ++c)
		{
			_keyCharMap[static_cast<sf::Keyboard::Key>(sf::Keyboard::Num0 + (c - '0'))] = c;
		}

		_keyCharMap[sf::Keyboard::Escape] = "Esc";
		_keyCharMap[sf::Keyboard::Space] = ' ';
		_keyCharMap[sf::Keyboard::Tab] = '\t';
		_keyCharMap[sf::Keyboard::Return] = '\n';
		_keyCharMap[sf::Keyboard::Comma] = ',';
		_keyCharMap[sf::Keyboard::Period] = '.';
		_keyCharMap[sf::Keyboard::Slash] = '/';
		_keyCharMap[sf::Keyboard::Backslash] = '\\';
		_keyCharMap[sf::Keyboard::Quote] = '\'';
		_keyCharMap[sf::Keyboard::SemiColon] = ';';
		_keyCharMap[sf::Keyboard::LBracket] = '[';
		_keyCharMap[sf::Keyboard::RBracket] = ']';
		_keyCharMap[sf::Keyboard::Dash] = '-';
		_keyCharMap[sf::Keyboard::Equal] = '=';
		_keyCharMap[sf::Keyboard::Tilde] = '`';
		_keyCharMap[sf::Keyboard::Left] = "Left";
		_keyCharMap[sf::Keyboard::Right] = "Right";
		_keyCharMap[sf::Keyboard::Up] = "Up";
		_keyCharMap[sf::Keyboard::Down] = "Down";

		for (int i = 1; i <= 24; ++i)
		{
			_keyCharMap[static_cast<sf::Keyboard::Key>(sf::Keyboard::F1 + i - 1)] = 'F' + i - 1;
		}
	}
}
