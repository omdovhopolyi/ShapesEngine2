#pragma once

#include "UIComponent.h"

namespace shen
{
    class UINode;

    struct InputType;
    struct CommandContext;

    class UIInputComponent
        : public UIComponent
    {
    public:
        void RegisterProperties() override;

        void SetInputPriority(int priority);
        int GetInputPriority() const;

        virtual bool ProcessInput(const InputType& inputType, const CommandContext& context) { return false; }

    private:
        int _inputPriority = 0;
    };
}
