#pragma once

#include <memory>

#define USING_PTRS(Type) \
    using Ptr = std::shared_ptr<Type>; \
    using WeakPtr = std::weak_ptr<Type>;