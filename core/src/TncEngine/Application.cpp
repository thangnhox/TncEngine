#include "Application.hpp"

#include <TncEngine/Events/ApplicationEvent.hpp>
#include <TncEngine/Log.hpp>

namespace TncEngine {

    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication))
        {
            TncEngine_TRACE(e);
        }
        if (e.IsInCategory(EventCategoryInput))
        {
            TncEngine_TRACE(e);
        }

        while (true);
    }

}