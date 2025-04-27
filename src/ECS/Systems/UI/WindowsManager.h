#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include "UI/UIWindow.h"
#include "Messenger/SubscriptionsContainer.h"
#include <vector>
#include <memory>
#include <string>

namespace shen
{
    struct InputType;
    struct CommandContext;
    struct UIWindowContext;

    class WindowsManager
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(WindowsManager);

    public:
        void Start() override;
        void Update() override;

        void OpenWindow(const UIWindowContext& context);
        void CloseTopWindow();
        void CloseWindow(const std::string& id);

        bool ProcessInput(const InputType& inputType, const CommandContext& context);

        const std::vector<std::unique_ptr<UIWindow>>& GetWindows() const { return _windows; }

    private:
        void InitSubscriptions();
        void UpdateWindows();
        void RemoveClosedWindows();

    private:
        std::vector<std::unique_ptr<UIWindow>> _windows;
        SubcriptionsContainer _subscriptions;
    };
}
