#pragma once

//#include "Utils/Singleton.h"
#include "Resources/AssetsManagerBase.h"

#include <memory>
#include <typeinfo>
#include <typeindex>
#include <map>

namespace shen
{
    class ResourcesManager
        //: public Singleton<ResourcesManager>
    {
    public:
        ResourcesManager();
        ~ResourcesManager();

        bool Init();        
        void Clear();

        template<class T>
        T* GetOrCreateAssetsManager();

    private:
        std::map<std::type_index, std::unique_ptr<AssetsManagerBase>> _resources;
    };

    template<class T>
    T* ResourcesManager::GetOrCreateAssetsManager()
    {
        const auto typeIndex = std::type_index(typeid(T));
        auto it = _resources.find(typeIndex);
        if (it != _resources.end())
        {
            return static_cast<T*>(it->second.get());
        }
        else
        {
            auto [it, isOk] = _resources.insert({ typeIndex, std::make_unique<T>() });
            if (isOk)
            {
                it->second->Init();
                return static_cast<T*>(it->second.get());
            }
        }

        // TODO assert
        return nullptr;
    }
}
