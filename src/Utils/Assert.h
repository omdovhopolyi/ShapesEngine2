#pragma once
#include <cassert>
#include <format>

// Use (void) to silent unused warnings.
#define Assert(exp, msg) assert(((void)msg, exp))