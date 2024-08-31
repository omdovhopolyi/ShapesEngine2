#pragma once

#include <string>
#include <map>
#include <memory>

namespace sf
{
    class RenderTarget;
    class Transform;
}

namespace shen
{
    class UINode;
    class UIWindow;

    class UIComponent
    {
    public:
        virtual void Init() {};
        virtual void RegisterReferences() {};
        virtual void Update(float dt) {};
        virtual void Draw(sf::RenderTarget& target, const sf::Transform& transform) const {};

        void SetId(const std::string& id) { _id = id; }
        const std::string& GetId() const { return _id; }

        void SetNode(UINode* node) { _node = node; }
        UINode* GetNode() const { return _node; }

        //void SetWindow(UIWindow* window) { _window = window; }
        UIWindow* GetWindow() const;

        void RegisterReference(const std::string& id, std::weak_ptr<UIComponent>* component);
        
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
        bool _dirty = true;
        std::map<std::string, std::string> _refsMap;
        std::map<std::string, std::weak_ptr<UIComponent>*> _references;
    };
}
