#pragma once

#include <typeinfo>
#include <typeindex>

#define TYPE_INDEX(Type) \
    public: \
        std::type_index GetTypeIndex() const { return std::type_index(typeid(Type)); } \
        std::string GetTypeName() const  { return #Type; }
