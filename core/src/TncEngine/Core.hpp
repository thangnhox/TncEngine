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

#define BIT(x) (1 << x)