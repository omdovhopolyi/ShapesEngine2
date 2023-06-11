#pragma once

namespace shen
{
    class System
    {
    public:
        virtual ~System() = default;

        virtual void Start() {};
        virtual void Update() {};
        virtual void Stop() {};
    };
}
