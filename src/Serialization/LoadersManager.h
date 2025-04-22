#pragma once

#include <Utils/Singleton.h>
#include <Serialization/Serialization.h>
#include <map>
#include <string>
#include "Serializable.h"

namespace shen
{
    class Serializable;

    class LoaderBase
    {
    public:
        ~LoaderBase() = default;
        virtual std::shared_ptr<Serializable> CreateAndLoad(const DataElementWrapper& serialization) = 0;
    };

    template<class T>
    class Loader
        : public LoaderBase
    {
    public:
        std::shared_ptr<Serializable> CreateAndLoad(const DataElementWrapper& element) override
        {
            auto serializable = std::make_shared<T>();
            serializable->RegisterProperties();
            serializable->Load(element);
            //serializable->AfterLoad();
            return serializable;
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
