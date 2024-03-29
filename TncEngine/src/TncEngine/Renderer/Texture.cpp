#include "TncPCH.hpp"
#include "Texture.hpp"

#include <TncEngine/Renderer/Renderer.hpp>
#include <Platform/OpenGL/OpenGLTexture.hpp>

namespace TncEngine {

    Ref<Texture2D> Texture2D::Create(const std::string &path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:         ASSERT_CORE(false, "RendererAPI::API::None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:       return CreateRef<OpenGLTexture2D>(path);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:         ASSERT_CORE(false, "RendererAPI::API::None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:       return CreateRef<OpenGLTexture2D>(width, height);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }
}