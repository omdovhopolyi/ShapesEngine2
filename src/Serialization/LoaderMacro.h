#pragma once

#include "Serialization/LoadersManager.h"

#define CLASS_LOADER_TEST(Type) \
    public: \
        static bool LoaderRegistered; \
        static bool RegisterLoader() \
        { \
            LoadersManager::Instance().RegisterLoader<Type>(#Type); \
            return true; \
        }

#define REGISTER_CLASS_LOADER_TEST(Type) \
    bool Type::LoaderRegistered = Type::RegisterLoader();