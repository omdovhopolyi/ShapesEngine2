#include "Command.h"
#include "Serialization/Types/SerializableFieldString.h"
#include "Serialization/Types/SerializableFieldBool.h"

namespace shen
{
    void Command::RegisterProperties()
    {
        RegisterVar<SerializableFieldString>(_id, "id");
        RegisterVar<SerializableFieldString>(_type, "type");
        RegisterVar<SerializableFieldBool>(_isGlobal, "global");
    }
}