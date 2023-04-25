#include "Window.hpp"

#include <TncPCH.hpp>

namespace TncEngine {

    static bool s_GLFWInitialized = false;

    Window::Window(const WindowProps &props)
    {
        Init(props);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::SetEventCallback(const EventCallbackFn &callback)
    {
        m_Data.EventCallback = callback;
    }

    void Window::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    std::unique_ptr<Window> Window::Create(const WindowProps &props)
    {
        return std::unique_ptr<Window>(new Window(props));
    }

    void Window::Init(const WindowProps &props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        TncEngine_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            ASSERT_CORE(success, "Could not initialize GLFW");

            s_GLFWInitialized = (success == GL_TRUE);
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

}