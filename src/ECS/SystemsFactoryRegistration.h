#pragma once

#include "SystemsFactory.h"
#include <typeindex>
#include <string>

#define SYSTEMS_FACTORY(Type) \
    public: \
        static bool registered; \
        static bool RegisterFactory(); \
        std::type_index GetTypeIndex() override { return std::type_index(typeid(Type)); } \
        std::string GetTypeName() override { return #Type; }

#define REGISTER_SYSTEMS_FACTORY(Type) \
    bool Type::RegisterFactory() \
    { \
        shen::SystemsFactory::Instance().RegisterSystemsFactory(#Type, [](){ return std::make_unique<Type>(); }); \
        return true; \
    } \
    bool Type::registered = Type::RegisterFactory();
