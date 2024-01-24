#pragma once

#include "Application.hpp"

extern TncEngine::Application* TncEngine::CreateApplication();

#ifdef _MAIN_PROGRAM_
int main(int argc, char** argv)
{
    TncEngine::Log::Init();
    TncEngine_CORE_INFO("Innitialize Log!");

    auto app = TncEngine::CreateApplication();

    TNC_PROFILE_BEGIN_SESSION("Runtime", "bin/Profiler/TncProfile-Runtime.json");
    app->run();
    TNC_PROFILE_END_SESSION();

    delete app;

    return 0;
}
#endif