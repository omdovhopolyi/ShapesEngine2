#include "EngineFacade.h"
#include "Engine.h"

namespace shen
{
    Engine* EngineFacade::_engine = nullptr;

    SystemsManager* EngineFacade::GetSystemsManager()
    {
        return _engine->_systems.get();
    }

    void EngineFacade::SetEnginePtr(Engine* engine)
    {
        _engine = engine;
    }
}
