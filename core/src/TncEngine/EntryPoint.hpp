#pragma once

#include "Application.hpp"

extern TncEngine::Application* TncEngine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = TncEngine::CreateApplication();
    app->run();
    delete app;

    return 0;
}