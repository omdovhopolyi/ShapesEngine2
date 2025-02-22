#pragma once

#include "InputCommandLoader.h"
#include "Serialization/Serialization.h"

namespace shen
{
    void InputCommandLoader::LoadTypeAndId(const Serialization& serialization, Command* command)
    {
        command->SetId(serialization.GetStr("id"));
        command->SetType(serialization.GetStr("type"));
        command->SetGlobal(serialization.GetBool("global"));
    }
}
