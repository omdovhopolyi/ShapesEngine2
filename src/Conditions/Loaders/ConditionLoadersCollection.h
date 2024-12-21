#pragma once

#include "Serialization/Serializer.h"
#include <map>
#include <string>
#include <memory>

namespace shen
{
    class ConditionLoader;

    class ConditionLoadersCollection
        : public Serializer<ConditionLoader, ConditionLoadersCollection>
    {};
}
