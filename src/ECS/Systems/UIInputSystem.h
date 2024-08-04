#pragma once

#include "BaseInputSystem.h"

namespace shen
{
    class WindowsManager;

    class UIInputSystem
        : public BaseInputSystem
    {
        SYSTEMS_FACTORY(UIInputSystem)

    public:
        void Start() override;
        void Update() override;

        bool OnKeyEvent(const KeyEvent& event) override;
        bool OnMouseButtonEvent(const MouseButtonEvent& event) override;
        bool OnMouseMoveEvent(const MouseMoveEvent& event) override;
        bool OnMouseWheelEvent(const MouseWheelEvent& event) override;

    private:
        WindowsManager* _windows = nullptr;
    };
}
