#pragma once

#include <Serialization/LoadersManager.h>
#include <Serialization/Loaders/LoaderDefault.h>
#include <Serialization/Loaders/LoaderECSComponent.h>

#define CLASS_LOADER(Type) \
    public: \
        static bool LoaderRegistered; \
        static bool RegisterLoader() \
        { \
            shen::LoadersManager::Instance().RegisterLoader(std::make_shared<shen::LoaderDefault<Type>>(), #Type); \
            return true; \
        }

#define COMP_LOADER(Type) \
    public: \
        static bool LoaderRegistered; \
        static bool RegisterLoader() \
        { \
            shen::LoadersManager::Instance().RegisterLoader(std::make_shared<shen::LoaderECSComponent<Type>>(), #Type); \
            return true; \
        }

#define REGISTER_LOADER(Type) \
    bool Type::LoaderRegistered = Type::RegisterLoader();