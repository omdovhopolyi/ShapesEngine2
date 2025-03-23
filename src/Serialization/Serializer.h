#pragma once

#include <Utils/Singleton.h>
#include <string>
#include <map>
#include <memory>

namespace shen
{
    template<class BaseLoader, class Collection>
    class Serializer
        : public Singleton<Collection>
    {
    public:
        template<class TLoader>
        void Register(const std::string& type)
        {
            _loaders[type] = std::make_unique<TLoader>();
        }

        BaseLoader* GetLoader(const std::string& type) const
        {
            if (auto it = _loaders.find(type); it != _loaders.end())
            {
                return it->second.get();
            }

            return nullptr;
        }

    protected:
        std::map<std::string, std::unique_ptr<BaseLoader>> _loaders;
    };
}
