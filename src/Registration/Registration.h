#pragma once

#include <typeindex>
#include <string>

#define CLASS_LOADER(LoaderType, Type) \
    public: \
        static bool registered; \
        static bool RegisterFactory() \
        { \
            LoaderType::Instance().Register<Type##Loader>(#Type); \
            return true; \
        }

#define REGISTER_CLASS_LOADER(Type) \
    bool Type::registered = Type::RegisterFactory();
