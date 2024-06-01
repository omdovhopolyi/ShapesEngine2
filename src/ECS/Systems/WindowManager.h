#pragma once

#include "BaseSystems/UpdateSystem.h"
#include "UI/Window.h"
#include <vector>
#include <memory>

namespace shen
{
    class WindowManager
        : public UpdateSystem
    {
    public:
        void Start();
        void Update();

        void OpenWindow(std::unique_ptr<Window>& window);

    private:
        std::vector<std::unique_ptr<Window>> _windows;
    };
}
