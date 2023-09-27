#pragma once

#include "AssetsManagerBase.h"

#include <string>
#include <map>
#include <memory>
#include <type_traits>

namespace shen
{
    template<class Type, class ContainerType>
    class AssetsManager
        : public AssetsManagerBase
    {
    public:
        virtual bool LoadAsset(const std::string& id, const std::string& path);
        virtual bool IsAssetLoaded(const std::string& id) const;
        virtual Type GetAsset(const std::string& id) const;

    protected:
        virtual std::pair<ContainerType, bool> LoadAssetImpl(const std::string& path) = 0;

    protected:
        std::map<std::string, ContainerType> _assets;
    };


    template<class Type, class ContainerType>
    bool AssetsManager<Type, ContainerType>::LoadAsset(const std::string& id, const std::string& path)
    {
        auto&& [asset, isOk] = LoadAssetImpl(path);
        if (isOk)
        {
            _assets[id] = asset;
            return true;
        }
        else
        {
            // TODO assert
            return false;
        }
    }

    template<class Type, class ContainerType>
    bool AssetsManager<Type, ContainerType>::IsAssetLoaded(const std::string& id) const
    {
        auto it = _assets.find(id);
        return it != _assets.end();
    }

    template<class Type, class ContainerType>
    Type AssetsManager<Type, ContainerType>::GetAsset(const std::string& id) const
    {
        auto it = _assets.find(id);
        if (it != _assets.end())
        {
            if constexpr (std::is_same_v<Type, ContainerType>)
            {
                return it->second;
            }
            else
            {
                return it->second.get();
            }
        }
        return nullptr;
    }
}
