#pragma once

#include "LoaderBase.h"

namespace shen
{
    template<class T>
    class LoaderDefault
        : public LoaderBase
    {
    public:
        std::shared_ptr<Serializable> CreateAndLoad(const DataElementWrapper& element) override
        {
            auto serializable = std::make_shared<T>();
            serializable->RegisterProperties();
            serializable->Load(element);
            return serializable;
        }
    };
}
