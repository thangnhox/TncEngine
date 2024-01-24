#include "Sandbox2D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <memory>
#include <chrono>

#include <TncEngine/Renderer/Renderer2D.hpp>

#include <Platform/OpenGL/OpenGLShader.hpp>

#define PROFILE_SCOPE(name) TncEngine::Timer timer##__LINE__(name, [&](const char* _name, float duration){ m_ProfileResults.push_back({_name, duration}); })

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnUpdate(TncEngine::Timestep ts)
{
    TNC_PROFILE_FUNCTION();

    m_FramesPerSecond = 1.0f / ts;

    m_FrameTime = ts * 1000.0f;

    {
        TNC_PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(ts);
    }

    {
        TNC_PROFILE_SCOPE("Renderer Prep");
        TncEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        TncEngine::RenderCommand::Clear();
    }

    // TncEngine::Renderer2D::BeginScene(TncEngine::ShaderLibrary::Get("FlatColorSquare"), [&](const TncEngine::Ref<TncEngine::Shader>& shader)
    // {
    //     std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformFloat4("u_Color", m_SquareColor);
    //     std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
    //     std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_Transform");
    // });
    // TncEngine::Renderer2D::Draw();

    {
        TNC_PROFILE_SCOPE("Renderer Draw");
        TncEngine::Renderer2D::BeginScene(TncEngine::ShaderLibrary::Get("TextureWithEditableColor"), m_CameraController.GetCamera());
        TncEngine::Renderer2D::Draw({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
        TncEngine::Renderer2D::Draw({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { m_SquareColor.b, m_SquareColor.g, m_SquareColor.r, m_SquareColor.a });
        TncEngine::Renderer2D::Draw({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Checkerboard);
        TncEngine::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::Text("FrameTime: %.3fms", m_FrameTime);
    ImGui::Text("Frames Per Second: %.3ffps", m_FramesPerSecond);

    ImGui::End();
}

void Sandbox2D::OnEvent(TncEngine::Event &e)
{
    m_CameraController.OnEvent(e);
}

void Sandbox2D::OnAttach()
{
    m_Checkerboard = TncEngine::Texture2D::Create("sandbox/assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}
