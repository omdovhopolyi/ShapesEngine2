#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include "Messenger/Events/Common.h"

namespace shen
{
    class BaseInputSystem
        : public UpdateSystem
    {
    public:
        void Update() override;

        virtual bool OnKeyEvent(const KeyEvent& event) { return false; }
        virtual bool OnMouseButtonEvent(const MouseButtonEvent& event) { return false; }
        virtual bool OnMouseMoveEvent(const MouseMoveEvent& event) { return false; }
        virtual bool OnMouseWheelEvent(const MouseWheelEvent& event) { return false; }
    };
}
