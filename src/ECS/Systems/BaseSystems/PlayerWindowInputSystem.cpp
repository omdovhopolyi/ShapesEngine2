#include <ECS/Systems/BaseSystems/PlayerWindowInputSystem.h>

namespace shen
{
    void PlayerWindowInputSystem::Start()
    {
        GenerateCharKeyMap();
        GenerateKeyCharMap();
    }
}
