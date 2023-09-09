#include "TncPCH.hpp"
#include "Shader.hpp"

#include <TncEngine/Renderer/Renderer.hpp>
#include <TncEngine/Renderer/OpenGLShader.hpp>

#include <TncEngine/Utils/StringUtils.hpp>

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

    ShaderLibrary &ShaderLibrary::Get()
    {
        static ShaderLibrary shaderLibrary;
        return shaderLibrary;
    }

    void ShaderLibrary::Add(const std::string &name, const Ref<Shader> &shader)
    {
        if (Exists(name))
        {
            TncEngine_CORE_ERROR("Shader id {0} already exists", name);
            TncEngine_CORE_ERROR("Shader library doesn't support overwriting existing shader!");
            return;
        }
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &filePath)
    {
        std::string name = StringUtils::PathToFileName(filePath, false);
        Add(name, Shader::Create(filePath));

        return m_Shaders[name];
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &filePath)
    {
        Add(name, Shader::Create(filePath));

        return m_Shaders[name];
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name)
    {
        if (!Exists(name))
        {
            TncEngine_CORE_FATAL("Shader ID {0} doesn't exists!", name);
            return nullptr;
        }

        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string &name)
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

}