#pragma once

#include "Application.hpp"

extern TncEngine::Application* TncEngine::CreateApplication();

#ifdef _MAIN_PROGRAM_
int main(int argc, char** argv)
{
    TncEngine::Log::Init();
    TncEngine_CORE_WARN("Innitialize Log!");

    auto app = TncEngine::CreateApplication();
    app->run();
    delete app;

    return 0;
}
#endif