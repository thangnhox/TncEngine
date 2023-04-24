#pragma once

#ifdef TNC_PLATFORM_WINDOWS
    #ifdef TNC_BUILD_DLL
        #define TncEngine_API __declspec(dllexport)
    #else
        #define TncEngine_API __declspec(dllimport)
    #endif
#else
    #define TncEngine_API
#endif

#ifdef ENABLE_ASSERT
    #define ASSERT_CORE(x, ...) { if(!(x)) { TncEngine_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #define ASSERT(x, ...) { if(!(x)) { TncEngine_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#else
    #define ASSERT_CORE
    #define ASSERT
#endif

#define BIT(x) (1 << x)