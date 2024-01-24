#pragma once

#include <memory>

#include "Core.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace TncEngine {

    class Log
    {
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    public:
        static void Init();

        static bool IsInited();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            if (!IsInited())
                Init();
            return s_CoreLogger;
        }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
        {
            if (!IsInited())
                Init();
            return s_ClientLogger;
        }
    };

}

// Core log macros
#define TncEngine_CORE_ERROR(...) TncEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TncEngine_CORE_INFO(...)  TncEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TncEngine_CORE_WARN(...)  TncEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TncEngine_CORE_TRACE(...) TncEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TncEngine_CORE_FATAL(...) TncEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TncEngine_ERROR(...)      TncEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TncEngine_INFO(...)       TncEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TncEngine_WARN(...)       TncEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TncEngine_TRACE(...)      TncEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TncEngine_FATAL(...)      TncEngine::Log::GetClientLogger()->critical(__VA_ARGS__)