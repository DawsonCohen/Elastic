#pragma once

#include <memory>

#include "Elastic/Log.h"

#ifdef EL_DEBUG
    #include <signal.h>
    #define EL_DEBUGBREAK() raise(SIGTRAP)

	#define EL_ENABLE_ASSERTS
#endif

#define EL_EXPAND_MACRO(x) x
#define EL_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)
#define EL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "Elastic/Log.h"
#include "Elastic/Assert.h"