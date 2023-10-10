#include "TncPCH.hpp"
#include "Renderer.hpp"

namespace TncEngine {

    struct RendererData
    {
        Ref<Shader> BoundShader;
        std::unordered_map<uint32_t, Ref<Texture>> BoundTextures;
    };

    static RendererData* s_Data = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
        if (!s_Data) s_Data = new RendererData();
        s_Data->BoundShader = nullptr;
    }

    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    // Bind shader
    void Renderer::BindShader(const Ref<Shader> &shader)
    {
        shader->Bind();
        s_Data->BoundShader = shader;
    }

    // Unbind shader
    void Renderer::UnbindShader()
    {
        s_Data->BoundShader->Unbind();
        s_Data->BoundShader = nullptr;
    }

    // Bind texture unit
    void Renderer::BindTexture(const Ref<Texture> &texture, uint32_t slot)
    {
        texture->Bind(slot);
        s_Data->BoundTextures[slot] = texture;
    }

    void Renderer::UnbindTexture(uint32_t slot)
    {
        s_Data->BoundTextures[slot]->Unbind(slot);
        s_Data->BoundTextures.erase(slot);
    }

    void Renderer::UnbindTexture(const Ref<Texture> &texture)
    {
        for (auto& [key, value] : s_Data->BoundTextures)
        {
            if (value == texture)
            {
                value->Unbind(key);
            }
        }
    }

    void Renderer::Submit(const Ref<VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::Submit(const std::string &name, const glm::mat4 &value)
    {
        s_Data->BoundShader->SetMat4(name, value);
    }

    void Renderer::Submit(const std::string &name, const glm::vec4 &value)
    {
        s_Data->BoundShader->SetFloat4(name, value);
    }

    void Renderer::Submit(const std::string &name, float value)
    {
        s_Data->BoundShader->SetFloat(name, value);
    }

    void Renderer::Submit(const std::string &name, int value)
    {
        s_Data->BoundShader->SetInt(name, value);
    }

    // Submit a lambda
    // use for some dynamic cast things
    void Renderer::Submit(const std::function<void(const Ref<Shader> &)> &func)
    {
        func(s_Data->BoundShader);
    }

    void Renderer::SetViewPort(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }

}