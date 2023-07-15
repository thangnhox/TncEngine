#include "TncPCH.hpp"
#include "VertexArray.hpp"

#include <TncEngine/Renderer/Renderer.hpp>
#include <TncEngine/Renderer/OpenGLVertexArray.hpp>

namespace TncEngine {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:         ASSERT_CORE(false, "RendererAPI::API::None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:       return new OpenGLVertexArray();
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

}
