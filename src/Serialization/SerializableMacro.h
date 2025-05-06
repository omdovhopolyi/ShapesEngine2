#pragma once

#include "LoaderMacro.h"
#include "TypeMacro.h"

#define SERIALIZABLE(Type) CLASS_LOADER(Type) TYPE_INDEX(Type)
#define SERIALIZABLE_COMP(Type) COMP_LOADER(Type)
