#include "TncPCH.hpp"
#include "Renderer.hpp"

namespace TncEngine {

    std::shared_ptr<Shader> Renderer::s_Shader = nullptr;

    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Bind(const std::shared_ptr<Shader> &shader)
    {
        shader->Bind();
        s_Shader = shader;
    }

    void Renderer::Submit(const std::string &name, const glm::mat4 &matrix)
    {
        s_Shader->UploadUniformMat4(name, matrix);
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}