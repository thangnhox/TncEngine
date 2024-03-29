#include "TncPCH.hpp"
#include "Buffer.hpp"

#include "Renderer.hpp"

#include <Platform/OpenGL/OpenGLBuffer.hpp>

namespace TncEngine {

    Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:   return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:   return CreateRef<OpenGLIndexBuffer>(indices, size);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

}