#pragma once

namespace shen
{
    class SystemsManager;

    class System
    {
    public:
        virtual ~System() = default;

        virtual void Init(SystemsManager* systems);
        virtual void Start() {};
        virtual void Stop() {};

    protected:
        SystemsManager* _systems = nullptr;
    };
}
