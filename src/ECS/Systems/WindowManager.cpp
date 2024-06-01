#include "WindowManager.h"

namespace shen
{
    void WindowManager::Start()
    {

    }

    void WindowManager::Update()
    {

    }

    void WindowManager::OpenWindow(std::unique_ptr<Window>& window)
    {
        _windows.push_back(std::move(window));
    }
}
