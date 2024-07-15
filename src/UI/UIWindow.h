#pragma once

#include "UINode.h"
#include "Components/UIInputComponent.h"
#include "Messenger/SubscriptionsContainer.h"
#include <string>
#include <memory>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class SystemsManager;
    class UINode;

    struct InputType;
    struct CommandContext;

    class UIWindow
    {
    public:
        virtual bool Init(const std::string& id, SystemsManager* systems);
        virtual void Update(float dt);
        virtual void Draw();

        SystemsManager* GetSystemsManager() const { return _systems; }

        const std::string& GetId() const;
        UINode* GetOrCreateRoot();

        void AddInputComponent(const std::string& nodeName, const std::shared_ptr<UIInputComponent>& component);
        void RemoveInputComponents(const std::string& nodeName);

        void SetInputComponentsDirty(bool dirty);
        bool IsInputComponentsDirty() const;

        bool ProcessInput(const InputType& inputType, const CommandContext& context);

    protected:
        void InitSubscriptions();
        void SetupComponentsArray();

    protected:
        SystemsManager* _systems = nullptr;
        std::string _id;
        std::unique_ptr<UINode> _root;
        std::map<std::string, std::weak_ptr<UIInputComponent>> _mappedInputComponents;
        std::vector<UIInputComponent*> _inputComponents;
        bool _inputComponentsDirty = false;
        SubcriptionsContainer _subscriptions;
    };
}
