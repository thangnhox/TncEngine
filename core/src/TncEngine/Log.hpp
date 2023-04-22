#pragma once

#include <memory>

#include "Core.hpp"
#include <spdlog/spdlog.h>

namespace TncEngine {

    class TncEngine_API Log
    {
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    };

}

// Core log macros
#define TncEngine_CORE_ERROR(...) ::TncEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TncEngine_CORE_INFO(...)  ::TncEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TncEngine_CORE_WARN(...)  ::TncEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TncEngine_CORE_TRACE(...) ::TncEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TncEngine_CORE_FATAL(...) ::TncEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TncEngine_ERROR(...)      ::TncEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TncEngine_INFO(...)       ::TncEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TncEngine_WARN(...)       ::TncEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TncEngine_TRACE(...)      ::TncEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TncEngine_FATAL(...)      ::TncEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)