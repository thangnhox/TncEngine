#include "TncPCH.hpp"
#include "Shader.hpp"

#include <TncEngine/Renderer/Renderer.hpp>
#include <Platform/OpenGL/OpenGLShader.hpp>

#include <TncEngine/Utils/StringUtils.hpp>

namespace TncEngine {

    Ref<Shader> Shader::Create(const std::string &filepath)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:   return CreateRef<OpenGLShader>(filepath);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:     ASSERT_CORE(false, "RendererAPI::API:None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL:   return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        ASSERT_CORE(false, "Unknown RendererAPI::API");
        return nullptr;
    }

    ShaderLibrary &ShaderLibrary::Get()
    {
        static ShaderLibrary shaderLibrary;
        return shaderLibrary;
    }

    void ShaderLibrary::AddImpl(const std::string &name, const Ref<Shader> &shader)
    {
        if (ExistsImpl(name))
        {
            TncEngine_CORE_ERROR("Shader id {0} already exists", name);
            TncEngine_CORE_ERROR("Shader library doesn't support overwriting existing shader!");
            return;
        }
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::LoadImpl(const std::string &filePath)
    {
        std::string name = StringUtils::PathToFileName(filePath, false);
        AddImpl(name, Shader::Create(filePath));

        return m_Shaders[name];
    }

    Ref<Shader> ShaderLibrary::LoadImpl(const std::string &name, const std::string &filePath)
    {
        AddImpl(name, Shader::Create(filePath));

        return m_Shaders[name];
    }

    Ref<Shader> ShaderLibrary::GetImpl(const std::string &name, const std::function<Ref<Shader>(const std::string &)> &exceptionHandler)
    {
        if (!ExistsImpl(name))
        {
            return exceptionHandler(name);
        }
        return m_Shaders[name];
    }

    Ref<Shader> ShaderLibrary::GetImpl(const std::string &name)
    {
        if (!ExistsImpl(name))
        {
            return m_NullHandler(name);
        }
        return m_Shaders[name];
    }

    bool ShaderLibrary::ExistsImpl(const std::string &name)
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

}