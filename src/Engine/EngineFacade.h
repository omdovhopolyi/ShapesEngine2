#pragma once

namespace shen
{
    class Engine;
    class SystemsManager;

    class EngineFacade
    {
    public:
        static SystemsManager* GetSystemsManager();
        static void SetEnginePtr(Engine* engine);

    private:
        static Engine* _engine;
    };
}
