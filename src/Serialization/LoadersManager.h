#pragma once

#include <Utils/Singleton.h>
#include <Serialization/Serialization.h>
#include <map>
#include <string>
#include "Asset.h"

namespace shen
{
    class LoaderBase
    {
    public:
        ~LoaderBase() = default;
        virtual std::shared_ptr<Asset> CreateAndLoad(const Serialization& serialization) = 0;
    };

    template<class T>
    class Loader
        : public LoaderBase
    {
    public:
        std::shared_ptr<Asset> CreateAndLoad(const Serialization& serialization) override
        {
            auto asset = std::make_shared<T>();

            for (auto& field : asset->GetFields())
            {
                field->Load(serialization);
            }

            return asset;
        }
    };

    class LoadersManager
        : public Singleton<LoadersManager>
    {
    public:
        template<class T>
        void RegisterLoader(const std::string& type)
        {
            _loaders.insert({ type, std::make_shared<Loader<T>>() });
        }

        std::shared_ptr<LoaderBase> GetLoader(const std::string& type);

    private:
        std::unordered_map<std::string, std::shared_ptr<LoaderBase>> _loaders;
    };
}
