#include "WindowsManager.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"
#include "Messenger/Events/Common.h"
#include "UI/UIWindow.h"
#include <SFML/Window/Keyboard.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(WindowsManager)

    void WindowsManager::Start()
    {
        InitSubscriptions();

        _loader = std::make_unique<UIWindowLoader>(_systems);
    }

    void WindowsManager::Update()
    {
        RemoveClosedWindows();
        UpdateWindows();
    }

    void WindowsManager::OpenWindow(const std::string& windowId)
    {
        auto window = std::make_unique<UIWindow>();
        _loader->LoadWindow(window.get(), windowId);
        window->Init(windowId, _systems);
        window->Open();
        _windows.push_back(std::move(window));        
    }

    void WindowsManager::CloseTopWindow()
    {
        if (!_windows.empty())
        {
            _windows.pop_back();
        }
    }

    void WindowsManager::ProcessInput(const InputType& inputType, const CommandContext& context)
    {
        for (auto& window : _windows)
        {
            const bool processed = window->ProcessInput(inputType, context);
            if (processed)
            {
                break;
            }
        }
    }

    void WindowsManager::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            if (event.code == sf::Keyboard::Key::V && event.type == InputEventType::Up)
            {
                OpenWindow("test_window");
            }

            if (event.code == sf::Keyboard::Key::B && event.type == InputEventType::Up)
            {
                CloseTopWindow();
            }
        });
    }

    void WindowsManager::UpdateWindows()
    {
        auto time = _systems->GetTime();

        for (auto& window : _windows)
        {
            window->Update(time.Dt());
        }
    }

    void WindowsManager::RemoveClosedWindows()
    {
        _windows.erase(std::remove_if(_windows.begin(), _windows.end(), [](const auto& window)
        {
            return window->GetState() == UIWindowState::Closed;

        }), _windows.end());
    }
}
