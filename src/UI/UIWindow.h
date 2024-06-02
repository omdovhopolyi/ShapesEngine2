#pragma once

#include "UINode.h"
#include <string>
#include <memory>
#include <tinyxml2/tinyxml2.h>

namespace shen
{
    class SystemsManager;
    class UINode;

    class UIWindow
    {
    public:
        virtual bool Init(const std::string& id, SystemsManager* systems);
        virtual void Update(float dt);
        virtual void Draw();

        SystemsManager* GetSystemsManager() const { return _systems; }

    protected:
        void LoadNode(UINode* node, tinyxml2::XMLElement* element); // TODO implement ui window loader

    protected:
        SystemsManager* _systems = nullptr;
        std::unique_ptr<UINode> _root;
    };
}
