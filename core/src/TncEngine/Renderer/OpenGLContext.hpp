#pragma once

#include <TncEngine/Renderer/GraphicsContext.hpp>

namespace TncEngine {

    class TncEngine_API OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };

}