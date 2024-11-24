#pragma once

#include "BaseSystems/System.h"
#include "Serialization/Serialization.h"

namespace shen
{
    class ObjectsAssetsCollectonSystem
        : public System
    {
        SYSTEMS_FACTORY(ObjectsAssetsCollectonSystem)

    public:
        void Load() override;
        const Serialization& GetData(const std::string& assetId) const;

    private:
        void LoadObjects();

    private:
        std::map<std::string, Serialization> _assets;
    };
}
