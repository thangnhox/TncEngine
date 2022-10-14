#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

namespace vulkanEngine { namespace graphics {

    class Window
    {

        private:
        uint32_t m_Width, m_Height;
        std::string m_Title;
        GLFWwindow* m_Window;

        public:
        Window();
        Window(uint32_t width, uint32_t height, std::string title);
        ~Window();

        Window(const Window&) = delete;
        Window &operator= (const Window&) = delete;

        uint32_t getWidth() const { return m_Width; }
        uint32_t getHeight() const { return m_Height; }
        bool closed() const { return glfwWindowShouldClose(m_Window); }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

        private:
        bool init();


    };

}}