#include "TncPCH.hpp"
#include "Renderer.hpp"

namespace TncEngine {

    Ref<Shader> Renderer::s_Shader;

    void Renderer::Init()
    {
        RenderCommand::Init();
        s_Shader = nullptr;
    }

    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Bind(const Ref<Shader> &shader)
    {
        shader->Bind();
        s_Shader = shader;
    }

    void Renderer::Submit(const Ref<VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    // Submit a lambda
    // use for some dynamic cast things
    void Renderer::Submit(const std::function<void(const Ref<Shader> &)> &func)
    {
        func(s_Shader);
    }

    void Renderer::SetViewPort(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }

}