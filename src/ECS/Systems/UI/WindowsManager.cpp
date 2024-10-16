#include "WindowsManager.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"
#include "Messenger/Events/Common.h"
#include "Messenger/Events/UIEvents.h"
#include "UI/UIWindow.h"
#include "UI/UIWindowLoader.h"
#include "UI/Components/Loaders/UIComponentLoader.h"
#include <SFML/Window/Keyboard.hpp>

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(WindowsManager)

    void WindowsManager::Start()
    {
        InitSubscriptions();
    }

    void WindowsManager::Update()
    {
        RemoveClosedWindows();
        UpdateWindows();
    }

    void WindowsManager::OpenWindow(const UIWindowContext& context)
    {
        auto window = std::make_unique<UIWindow>();
        UIWindowLoader::Instance().LoadWindow(_systems, window.get(), context.windowId);
        window->Init(context);
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

    bool WindowsManager::ProcessInput(const InputType& inputType, const CommandContext& context)
    {
        for (auto& window : _windows)
        {
            const bool processed = window->ProcessInput(inputType, context);
            if (processed)
            {
                return true;
            }
        }

        return false;
    }

    void WindowsManager::InitSubscriptions()
    {
        _subscriptions.Subscribe<KeyEvent>([this](const KeyEvent& event)
        {
            if (event.code == sf::Keyboard::Key::V && event.type == InputEventType::Up)
            {
                UIWindowContext context;
                context.windowId = "test_window";
                context.systems = _systems;
                OpenWindow(context);
            }

            if (event.code == sf::Keyboard::Key::B && event.type == InputEventType::Up)
            {
                CloseTopWindow();
            }
        });

        _subscriptions.Subscribe<OpenWindowEvent>([this](const OpenWindowEvent& event)
        {
            OpenWindow(event.context);
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
