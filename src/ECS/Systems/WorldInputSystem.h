#pragma once

#include "BaseInputSystem.h"
#include "Messenger/Events/Common.h"
#include "Input/InputType.h"
//#include "Utils/Types.h"
//#include "Enums/Direction.h"
//#include "Enums/MouseButtonEnum.h"
//#include "Enums/InputEventTypeEnum.h"
//#include "Enums/KeyModeEnum.h"

#include "Commands/Command.h"

#include <memory>

namespace shen
{
    /*struct InputType
    {
        int keyCode = -1;
        MouseButton mouseButton = MouseButton::None;
        InputEventType type = InputEventType::Undefined;
        bool alt = false;
        bool shift = false;
        bool ctrl = false;

        friend bool operator < (const InputType& left, const InputType& right);
        friend bool operator == (const InputType& left, const InputType& right);
    };*/

    class WorldInputSystem
        : public BaseInputSystem
    {
    public:
        using InputCode = int;
        using CommandsMap = std::map<InputCode, std::shared_ptr<Command>>;
        using WeakCommands = std::vector<std::weak_ptr<Command>>;

        void Start() override;
        void Update() override;

        bool OnKeyEvent(const KeyEvent& event) override;
        bool OnMouseButtonEvent(const MouseButtonEvent& event) override;
        bool OnMouseMoveEvent(const MouseMoveEvent& event) override;
        bool OnMouseWheelEvent(const MouseWheelEvent& event) override;

    protected:
        virtual void InitActionCallbacks();
        void LoadConfig();
        
    protected:
        std::map<InputType, Command*> _actions;
        std::vector<std::pair<Command*, CommandContext>> _toProcess;
    };
}
