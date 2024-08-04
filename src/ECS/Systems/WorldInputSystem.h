#pragma once

#include "BaseInputSystem.h"
#include "Messenger/Events/Common.h"
#include "Input/InputType.h"
#include "Commands/Command.h"
#include <memory>

namespace shen
{
    class WorldInputSystem
        : public BaseInputSystem
    {
        SYSTEMS_FACTORY(WorldInputSystem)

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
