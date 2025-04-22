#pragma once

#include "LoaderMacro.h"
#include "TypeMacro.h"

#define SERIALIZABLE(Type) CLASS_LOADER_TEST(Type) TYPE_INDEX(Type)
