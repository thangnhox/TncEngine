#include "TncPCH.hpp"
#include "Window.hpp"

#include <TncEngine/Renderer/Renderer.hpp>

#include <Platform/OpenGL/OpenGLWindow.hpp>

namespace TncEngine {

    Scope<Window> Window::Create(const WindowProps &props)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:            ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:          return CreateScope<OpenGLWindow>(props);
        }

        TncEngine_CORE_FATAL("Invalid API Enum {0}", (int)Renderer::GetAPI());
        return nullptr;
    }

}