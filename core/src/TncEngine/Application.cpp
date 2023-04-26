#include "Application.hpp"

#include <TncEngine/Events/ApplicationEvent.hpp>
#include <TncPCH.hpp>

namespace TncEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose));

        TncEngine_CORE_TRACE("{0}", e);
    }

    void Application::run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowClosedEvent &e)
    {
        m_Running = false;
        return true;
    }

}