#include "TncPCH.hpp"
#include "VertexArray.hpp"

#include <TncEngine/Renderer/Renderer.hpp>
#include <TncEngine/Renderer/OpenGLVertexArray.hpp>

namespace TncEngine {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:         ASSERT_CORE(false, "RendererAPI::None is currently not supported"); return nullptr;
            case RendererAPI::OpenGL:       return new OpenGLVertexArray();
        }

        ASSERT_CORE(false, "Unknown RendererAPI");
        return nullptr;
    }

}
