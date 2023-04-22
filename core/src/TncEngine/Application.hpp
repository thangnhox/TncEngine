#pragma once

#include "Core.hpp"

namespace TncEngine {

    class TncEngine_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    };

    // TOBE: define in client
    Application* CreateApplication();

}