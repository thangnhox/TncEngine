#include "Sandbox2D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <memory>

#include <Platform/OpenGL/OpenGLShader.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnUpdate(TncEngine::Timestep ts)
{
    m_CameraController.OnUpdate(ts);

    TncEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    TncEngine::RenderCommand::Clear();

    TncEngine::Renderer::BeginScene();

    TncEngine::Renderer::Bind(TncEngine::ShaderLibrary::Get("FlatColorSquare"));
    std::dynamic_pointer_cast<TncEngine::OpenGLShader>(TncEngine::ShaderLibrary::Get("FlatColorSquare"))->UploadUniformFloat4("u_Color", m_SquareColor);

    TncEngine::Renderer::Bind(TncEngine::ShaderLibrary::Get("FlatColorSquare"));
    TncEngine::Renderer::Submit([&](const TncEngine::Ref<TncEngine::Shader>& shader)
    {
        std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
        std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_Transform", glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    });
    TncEngine::Renderer::Submit(m_SquareVertexArray);

    TncEngine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(TncEngine::Event &e)
{
    m_CameraController.OnEvent(e);
}

void Sandbox2D::OnAttach()
{
    m_SquareVertexArray = TncEngine::VertexArray::Create();

    float squareVertices[] = {
        -0.5f, -0.5f, -0.0f,
         0.5f, -0.5f, -0.0f,
         0.5f,  0.5f, -0.0f,
        -0.5f,  0.5f, -0.0f 
    };

    TncEngine::Ref<TncEngine::VertexBuffer> squareVertexBuffer;
    squareVertexBuffer = TncEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

    squareVertexBuffer->SetLayout({
        { TncEngine::ShaderDataType::Float3, "a_Position"},
    });
    m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    TncEngine::Ref<TncEngine::IndexBuffer> squareIndexBuffer;
    squareIndexBuffer = TncEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

    auto& shaderLibrary = TncEngine::ShaderLibrary::Get();

    shaderLibrary.Load("FlatColorSquare", "sandbox/assets/shaders/FlatColorSquare.glsl");
}

void Sandbox2D::OnDetach()
{
}
