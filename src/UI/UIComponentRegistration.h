#pragma once

#include "UI/UIWindowLoader.h"
#include <typeindex>
#include <string>

#define UI_COMPONENT_LOADER(LoaderType, CompType) \
    public: \
        static bool registered; \
        static bool RegisterFactory() \
        { \
            UIWindowLoader::Instance().RegisterComponentLoader<LoaderType>(#CompType); \
            return true; \
        }

#define REGISTER_UI_COMPONENT_LOADER(Type) \
    bool Type::registered = Type::RegisterFactory();