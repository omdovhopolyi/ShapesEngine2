#pragma once

namespace shen
{
    class SystemsManager;

    class Window
    {
    public:
        virtual void Init(SystemsManager* systems);
        virtual void Update(float dt);
        virtual void Draw();

    protected:
        SystemsManager* _systems = nullptr;
    };
}
