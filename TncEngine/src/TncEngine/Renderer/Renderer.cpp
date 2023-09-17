#include "TncPCH.hpp"
#include "Renderer.hpp"

#include <Platform/OpenGL/OpenGLShader.hpp>

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

    void Renderer::Submit(const std::string &name, const glm::mat4 &matrix)
    {
        std::dynamic_pointer_cast<OpenGLShader>(s_Shader)->UploadUniformMat4(name, matrix);
    }

    void Renderer::Submit(const Ref<VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::SetViewPort(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }

}