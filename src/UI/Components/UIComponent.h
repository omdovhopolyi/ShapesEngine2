#pragma once

#include <string>
#include <map>
#include <memory>
#include "Serialization/Serializable.h"

namespace sf
{
    class RenderTarget;
    class Transform;
}

namespace shen
{
    class UINode;
    class UIWindow;
    class UIComponent;

    class IUIComponentWrapper
    {
    public:
        virtual ~IUIComponentWrapper();

        std::weak_ptr<UIComponent> GetComponentPtr()
        {
            return _reference;
        }

        void SetComponent(std::weak_ptr<UIComponent> component)
        {
            _reference = component;
        }

    protected:
        std::weak_ptr<UIComponent> _reference;
    };

    template<class T>
    class UIComponentWrapper 
        : public IUIComponentWrapper
    {
    public:
        std::weak_ptr<T> GetWeak()
        {
            return std::static_pointer_cast<T>(_reference);
        }

        std::shared_ptr<T> GetShared()
        {
            return std::static_pointer_cast<T>(_reference.lock());
        }

        T* Get()
        {
            if (auto ref = _reference.lock())
            {
                return static_cast<T*>(ref.get());
            }

            return nullptr;
        }
    };

    class UIComponent
        : public Serializable
    {
    public:
        virtual ~UIComponent();

        void RegisterProperties() override;

        virtual void Init() {};
        virtual void OnWindowOpen() {};
        virtual void RegisterReferences() {};
        virtual void Update(float dt) {};
        virtual void Draw(sf::RenderTarget& target, const sf::Transform& transform) const {};

        void SetId(const std::string& id) { _id = id; }
        const std::string& GetId() const { return _id; }

        void SetNode(UINode* node) { _node = node; }
        UINode* GetNode() const { return _node; }

        UIWindow* GetWindow() const;

        void RegisterReference(const std::string& id, IUIComponentWrapper& component);
        
        template<class Comp>
        const std::weak_ptr<Comp>& GetReference(const std::string& id) const
        {
            if (auto it = _references.find(id); it != _references.end())
            {
                if (auto compPtr = it->second.lock())
                {
                    return std::dynamic_pointer_cast<Comp>(compPtr);
                }
            }

            return nullptr;
        }

        void ClearReferencesData();
        void AddReferenceData(const std::string& id, const std::string& compId);
        const std::string& GetReferenceData(const std::string& id) const;

        void ResolveReferences();

    protected:
        UINode* _node = nullptr;
        std::string _id;
        std::map<std::string, std::string> _refsMap;
        std::map<std::string, IUIComponentWrapper*> _references;
    };
}
