#pragma once

#include "ConditionLoadersCollection.h"
#include "Registration/Registration.h"
#include "Conditions/ConditionBase.h"
#include <memory>

namespace shen
{
    class Serialization;

    class ConditionLoader
    {
    public:
        virtual ~ConditionLoader() = default;
        virtual std::unique_ptr<ConditionBase> LoadCondition(const Serialization&) { return nullptr; }
    };
}
