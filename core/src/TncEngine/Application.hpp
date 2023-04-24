#pragma once

#include <TncEngine/Core.hpp>
#include <TncEngine/Events/Event.hpp>

#include <TncEngine/Window.hpp>

namespace TncEngine {

    class TncEngine_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running;
    };

    // TOBE: define in client
    Application* CreateApplication();

}