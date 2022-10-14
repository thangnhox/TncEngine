#include "window.hpp"

namespace vulkanEngine { namespace graphics {

    Window::Window(uint32_t width, uint32_t height, std::string title)
        : m_Width{width}, m_Height{height}, m_Title{title}
    {
        if (!init())
        {
            std::cout << "failed to init window" << std::endl;
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
    {
        if (glfwCreateWindowSurface(instance, m_Window, nullptr, surface) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create window surface");
        }
    }

    bool Window::init()
    {
        if (!glfwInit())
        {
            std::cout << "failed to init GLFW" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        if (!m_Window)
        {
            std::cout << "failed to create window!" << std::endl;
            return false;
        }

        return true;
    }

}}