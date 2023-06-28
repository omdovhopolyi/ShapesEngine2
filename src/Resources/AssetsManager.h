#pragma once

#include "AssetsManagerBase.h"

#include <string>
#include <map>
#include <memory>

namespace shen
{
    template<class T>
    class AssetsManager
        : public AssetsManagerBase
    {
    public:
        virtual bool LoadAsset(const std::string& id, const std::string& path);
        virtual bool IsAssetLoaded(const std::string& id) const;
        virtual T GetAsset(const std::string& id) const;

    protected:
        virtual std::pair<T, bool> LoadAssetImpl(const std::string& path) = 0;

    protected:
        std::map<std::string, T> _assets;
    };


    template<class T>
    bool AssetsManager<T>::LoadAsset(const std::string& id, const std::string& path)
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

    template<class T>
    bool AssetsManager<T>::IsAssetLoaded(const std::string& id) const
    {
        auto it = _assets.find(id);
        return it != _assets.end();
    }

    template<class T>
    T AssetsManager<T>::GetAsset(const std::string& id) const
    {
        auto it = _assets.find(id);
        if (it != _assets.end())
        {
            return it->second;
        }
        return nullptr;
    }
}
