#pragma once

#include <memory>

#ifdef TNC_DEBUG
    #define ENABLE_ASSERT
#endif

#ifdef ENABLE_ASSERT
    #define ASSERT_CORE(x, ...) { if(!(x)) { TncEngine_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #define ASSERT(x, ...) { if(!(x)) { TncEngine_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#else
    #define ASSERT_CORE(x, ...)
    #define ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define TNC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace TncEngine {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}
