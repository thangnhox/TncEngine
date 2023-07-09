#include "TncPCH.hpp"
#include "OpenGLContext.hpp"

namespace TncEngine {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle)
    {
        ASSERT_CORE(windowHandle, "Window Handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT_CORE(status, "Failed to initialize Glad");

        TncEngine_CORE_INFO("OpenGL Info:");
        TncEngine_CORE_INFO("   Vendor: {0}", (const char*) glGetString(GL_VENDOR));
        TncEngine_CORE_INFO("   Renderer: {0}", (const char*) glGetString(GL_RENDERER));
        TncEngine_CORE_INFO("   Version: {0}", (const char*) glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}