#pragma once

#include "BaseSystems/System.h"
#include "Serialization/DataElementWrapper.h"

namespace shen
{
    class ObjectsAssetsCollectonSystem
        : public System
    {
        SYSTEMS_FACTORY(ObjectsAssetsCollectonSystem)

    public:
        void Load() override;
        const DataElementWrapper* GetData(const std::string& assetId) const;

    private:
        void LoadObjects();

    private:
        std::map<std::string, std::unique_ptr<DataElementWrapper>> _assets;
    };
}
