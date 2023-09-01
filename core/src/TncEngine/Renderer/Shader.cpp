#include "TncPCH.hpp"
#include "Shader.hpp"

#include <TncEngine/Renderer/Renderer.hpp>
#include <TncEngine/Renderer/OpenGLShader.hpp>

namespace TncEngine {
    
    Ref<Shader> Shader::Create(const std::string &filepath)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(filepath);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

}