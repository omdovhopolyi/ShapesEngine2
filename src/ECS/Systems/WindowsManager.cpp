#include "WindowsManager.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"
#include "Messenger/Events/Common.h"
#include "UI/UIWindow.h"
#include <SFML/Window/Keyboard.hpp>

namespace shen
{
    void WindowsManager::Start()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            if (event.code == sf::Keyboard::Key::V && event.type == InputEventType::Up)
            {
                OpenWindow("test_window");
            }

            if (event.code == sf::Keyboard::Key::B && event.type == InputEventType::Up)
            {
                CloseWindow();
            }
        });
    }

    void WindowsManager::Update()
    {
        auto time = _systems->GetTime();

        for (auto& window : _windows)
        {
            window->Update(time.Dt());
        }
    }

    void WindowsManager::OpenWindow(const std::string& windowId)
    {
        auto window = std::make_unique<UIWindow>();

        const bool isInited = window->Init(windowId, _systems);
        if (isInited)
        {
            _windows.push_back(std::move(window));
        }
    }

    void WindowsManager::CloseWindow()
    {
        _windows.pop_back();
    }
}
