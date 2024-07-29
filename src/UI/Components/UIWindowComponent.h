#pragma once

#include <string>

namespace shen
{
    class UIWindow;

    class UIWindowComponent
    {
    public:
        virtual void Init() {};
        virtual void Update(float dt) {};

    protected:
        UIWindow* _window = nullptr;
    };
}
