#pragma once

#include <Utils/Singleton.h>
#include <map>
#include <string>
#include "Serializable.h"
#include "Loaders/LoaderDefault.h"
#include "Loaders/LoaderECSComponent.h"

namespace shen
{
    class LoadersManager
        : public Singleton<LoadersManager>
    {
    public:
        void RegisterLoader(const std::shared_ptr<LoaderBase>& loader, const std::string& type)
        {
            _loaders.insert({ type, loader });
        }

        /*template<class T>
        void RegisterComponentLoader(const std::string& type)
        {
            _loaders.insert({ type, std::make_shared<LoaderECSComponent<T>>() });
        }*/

        std::shared_ptr<LoaderBase> GetLoader(const std::string& type);

    private:
        std::unordered_map<std::string, std::shared_ptr<LoaderBase>> _loaders;
    };
}
