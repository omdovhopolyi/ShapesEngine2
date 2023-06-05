#pragma once

#include "Utils/Singleton.h"



namespace shen
{
    class SystemsManager;
    class EcsWorld;

    class ManagersProvider
        : public Singleton<ManagersProvider>
    {
    public:
        bool Init();

        void Clear();

    private:
        
    };

}
