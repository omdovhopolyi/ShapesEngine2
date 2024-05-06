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
        using LoadParams = std::map<std::string, std::string>;

    public:
        bool Init() override { return true; }
        void Clear() override {};

        virtual bool LoadAsset(const std::string& id, const LoadParams& params);
        virtual bool LoadAsset(const std::string& id, const std::string& path);
        virtual bool IsAssetLoaded(const std::string& id) const;
        virtual Type GetAsset(const std::string& id) const;

    protected:
        virtual std::pair<ContainerType, bool> LoadAssetImpl(const LoadParams& params) { return {}; }
        virtual std::pair<ContainerType, bool> LoadAssetImpl(const std::string& path) { return {}; }

    protected:
        std::map<std::string, ContainerType> _assets;
    };

    template<class Type, class ContainerType>
    bool AssetsManager<Type, ContainerType>::LoadAsset(const std::string& id, const LoadParams& params)
    {
        auto&& [asset, isOk] = LoadAssetImpl(params);
        if (isOk)
        {
            _assets[id] = std::move(asset);
            return true;
        }
        else
        {
            //Assert(false, "[AssetsManager::LoadAsset] Can not load asset '" + id + "'");
            return false;
        }
    }

    template<class Type, class ContainerType>
    bool AssetsManager<Type, ContainerType>::LoadAsset(const std::string& id, const std::string& path)
    {
        auto&& [asset, isOk] = LoadAssetImpl(path);
        if (isOk)
        {
            _assets[id] = std::move(asset);
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
