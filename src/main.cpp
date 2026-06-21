
#ifndef SHEN_NO_MAIN

#include "Engine/Engine.h"
#include "Engine/EngineFacade.h"

#if (defined(_WIN32) || defined(_WIN64)) && defined(SHEN_WIN_MAIN)
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
    shen::Engine engine;
    shen::EngineFacade::SetEnginePtr(&engine);

    engine.Initialize();
    engine.Run();
    engine.Destroy();

    return 0;
}

#endif
