#include "Application.hpp"

#include <TncEngine/Events/ApplicationEvent.hpp>
#include <TncPCH.hpp>

namespace TncEngine {

    Application::Application()
    {
        m_Window = Window::Create();
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
            m_Running = !m_Window->ShouldClose();
        }
    }

}