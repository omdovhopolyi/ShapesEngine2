#pragma once

#include "BaseSystems/UpdateSystem.h"
#include "UI/UIWindow.h"
#include "UI/UIWindowLoader.h"
#include "Messenger/SubscriptionsContainer.h"
#include <vector>
#include <memory>
#include <string>

namespace shen
{
    class WindowsManager
        : public UpdateSystem
    {
    public:
        void Start() override;
        void Update() override;

        void OpenWindow(const std::string& windowId);
        void CloseWindow();

        const std::vector<std::unique_ptr<UIWindow>>& GetWindows() const { return _windows; }

    private:
        void InitSubscriptions();

    private:
        std::vector<std::unique_ptr<UIWindow>> _windows;
        std::unique_ptr<UIWindowLoader> _loader;
        SubcriptionsContainer _subscriptions;
    };
}
