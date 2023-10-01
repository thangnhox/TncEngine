#include "TncPCH.hpp"
#include "RenderCommand.hpp"

#include <Platform/OpenGL/OpenGLRendererAPI.hpp>

namespace TncEngine {

    RendererAPI* RenderCommand::s_RendererAPI = nullptr;

    void RenderCommand::Init()
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:            ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return;
            case RendererAPI::API::OpenGL:          s_RendererAPI = new OpenGLRendererAPI(); break;
        }

        s_RendererAPI->Init();
    }

}