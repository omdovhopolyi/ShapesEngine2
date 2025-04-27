#pragma once

#include <Serialization/LoadersManager.h>

#define CLASS_LOADER(Type) \
    public: \
        static bool LoaderRegistered; \
        static bool RegisterLoader() \
        { \
            shen::LoadersManager::Instance().RegisterLoader<Type>(#Type); \
            return true; \
        }

#define REGISTER_CLASS_LOADER(Type) \
    bool Type::LoaderRegistered = Type::RegisterLoader();