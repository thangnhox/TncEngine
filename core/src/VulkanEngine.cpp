#include "VulkanEngine.hpp"

namespace vulkanEngine
{
    VulkanEngine::VulkanEngine()
        : m_Window{1280, 720, "Template"},
        m_Pipeline{}
    {
    }

    VulkanEngine::VulkanEngine(const std::string& vertextShader, const std::string& fragmentShader)
        : m_Window{1280, 720, "Template"},
        m_Pipeline{vertextShader, fragmentShader}
    {
    }

    VulkanEngine::~VulkanEngine()
    {
    }

    int VulkanEngine::run()
    {
        int status = 0;

        while (!m_Window.closed())
        {
            glfwPollEvents();
        }

        return status;
        // status return code
        //  0   :   exit
        // -1   :   restart
    }

}