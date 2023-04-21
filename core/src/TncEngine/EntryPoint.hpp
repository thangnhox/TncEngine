#pragma once

#include "Application.hpp"

extern TncEngine::Application* TncEngine::CreateApplication();

int main(int argc, char** argv)
{
    TncEngine::Log::Init();
    TncEngine_CORE_WARN("Innitialize Log!");
    int a = 10;
    TncEngine_INFO("Hello! Var={0}", a);

    auto app = TncEngine::CreateApplication();
    app->run();
    delete app;

    return 0;
}