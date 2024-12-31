#pragma once

#include "UINode.h"
#include "Components/UIInputComponent.h"
#include "Messenger/SubscriptionsContainer.h"
#include "UI/UIWindowContext.h"
#include <string>
#include <memory>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class SystemsManager;
    class UINode;

    struct InputType;
    struct CommandContext;

    enum class UIWindowState
    {
        Closed,
        Open
    };

    class UIWindow
    {
    public:
        virtual bool Init(const UIWindowContext& context);
        virtual void Update(float dt);
        virtual void Draw();

        SystemsManager* GetSystemsManager() const { return _context.systems; }

        const std::string& GetId() const;
        const std::shared_ptr<UINode>& GetOrCreateRoot();

        void MapComponent(const std::string& id, const std::shared_ptr<UIComponent>& component);
        void MapInputComponent(const std::string& id, const std::shared_ptr<UIInputComponent>& component);
        void MapNode(const std::string& id, const std::shared_ptr<UINode>& node);

        void SetComponentsDirty(bool dirty);
        bool IsComponentsDirty() const;

        void ResolveReferences();
        void InitComponents();

        std::weak_ptr<UIComponent> GetComponent(const std::string& id) const;
        std::weak_ptr<UIInputComponent> GetInputComponent(const std::string& id) const;
        std::weak_ptr<UINode> GetNode(const std::string& id) const;

        bool ProcessInput(const InputType& inputType, const CommandContext& context);

        void Open();
        void Close();

        void OnOpen();

        void SetState(UIWindowState state) { _state = state; }
        UIWindowState GetState() const { return _state; }

    protected:
        void InitSubscriptions();
        void RemoveExpiredComponents();
        void SetupInputComponentsArray();

        static void OnOpen(UINode* node);
        static void InitComponentsForNode(UINode* node);

    protected:
        UIWindowContext _context;
        UIWindowState _state = UIWindowState::Closed;
        std::shared_ptr<UINode> _root;
        std::map<std::string, std::weak_ptr<UIInputComponent>> _mappedInputComponents;
        std::map<std::string, std::weak_ptr<UIComponent>> _mappedComponents;
        std::map<std::string, std::weak_ptr<UINode>> _mappedNodes;
        std::vector<UIInputComponent*> _inputComponents;
        bool _componentsDirty = false;
        SubcriptionsContainer _subscriptions;
    };
}
