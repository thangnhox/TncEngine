#define _MAIN_PROGRAM_
#include <TncEngine.hpp>

// #include <glm/vec3.hpp>                 // glm::vec3
// #include <glm/vec4.hpp>                 // glm::vec4
// #include <glm/mat4x4.hpp>               // glm::mat4
// #include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
// glm::mat4 camera(float Translate, glm::vec2 const &Rotate)
// {
//     glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
//     glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//     View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//     View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//     glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//     return Projection * View * Model;
// }

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include <Platform/OpenGL/OpenGLShader.hpp>

#include <TncEngine/Renderer/Renderer2D.hpp>

#include "Sandbox2D.hpp"

#include <TncEngine/Utils/Timestep.hpp>

class ExampleLayer : public TncEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_CameraController(1280.0f / 720.0f)
    {
        m_VertexArray = TncEngine::VertexArray::Create();
        m_SquareVertexArray = TncEngine::VertexArray::Create();

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        float squareVertices[] = {
            -0.5f, -0.5f, -0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.0f, 0.0f, 1.0f
        };

        TncEngine::Ref<TncEngine::VertexBuffer> vertexBuffer;
        TncEngine::Ref<TncEngine::VertexBuffer> squareVertexBuffer;
        vertexBuffer = TncEngine::VertexBuffer::Create(vertices, sizeof(vertices));
        squareVertexBuffer = TncEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        vertexBuffer->SetLayout({
            { TncEngine::ShaderDataType::Float3, "a_Position" },
            { TncEngine::ShaderDataType::Float4, "a_Color" }
        });
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        squareVertexBuffer->SetLayout({
            { TncEngine::ShaderDataType::Float3, "a_Position"},
            { TncEngine::ShaderDataType::Float2, "a_TexCoord"}
        });
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        TncEngine::Ref<TncEngine::IndexBuffer> indexBuffer;
        indexBuffer = TncEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        TncEngine::Ref<TncEngine::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer = TncEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        auto& shaderLibrary = TncEngine::ShaderLibrary::Get();

        shaderLibrary.Load("ColorTriangle", "sandbox/assets/shaders/Triangle.glsl");
        shaderLibrary.Load("FlatSquare", "sandbox/assets/shaders/FlatSquare.glsl");
        shaderLibrary.Load("Texture", "sandbox/assets/shaders/Texture.glsl");

        m_Checkerboard = TncEngine::Texture2D::Create("sandbox/assets/textures/Checkerboard.png");
        m_ChernoLogo = TncEngine::Texture2D::Create("sandbox/assets/textures/ChernoLogo.png");

        TncEngine::Renderer::BindShader(shaderLibrary.Get("Texture"));
        std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shaderLibrary.Get("Texture"))->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(TncEngine::Timestep ts) override
    {
        m_CameraController.OnUpdate(ts);

        TncEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        TncEngine::RenderCommand::Clear();

        TncEngine::Renderer::BeginScene();

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        TncEngine::Renderer::BindShader(TncEngine::ShaderLibrary::Get("FlatSquare"));
        std::dynamic_pointer_cast<TncEngine::OpenGLShader>(TncEngine::ShaderLibrary::Get("FlatSquare"))->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos = glm::vec3(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                TncEngine::Renderer::BindShader(TncEngine::ShaderLibrary::Get("FlatSquare"));
                TncEngine::Renderer::Submit([&](const TncEngine::Ref<TncEngine::Shader>& shader)
                {
                    std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
                    std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

                });
                TncEngine::Renderer::Submit(m_SquareVertexArray);
            }
        }

        auto texture = TncEngine::ShaderLibrary::Get("Texture");

        m_Checkerboard->Bind();
        TncEngine::Renderer::BindShader(texture);
        TncEngine::Renderer::Submit([&](const TncEngine::Ref<TncEngine::Shader>& shader)
        {
            std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
            std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_Transform", glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        });
        TncEngine::Renderer::Submit(m_SquareVertexArray);

        m_ChernoLogo->Bind();
        TncEngine::Renderer::BindShader(texture);
        TncEngine::Renderer::Submit([&](const TncEngine::Ref<TncEngine::Shader>& shader)
        {
            std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
            std::dynamic_pointer_cast<TncEngine::OpenGLShader>(shader)->UploadUniformMat4("u_Transform", glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        });
        TncEngine::Renderer::Submit(m_SquareVertexArray);

        // TncEngine::Renderer::Bind(m_Shader);
        // TncEngine::Renderer::Submit("u_ViewProjection", m_CameraController.GetViewProjectionMatrix());
        // TncEngine::Renderer::Submit("u_Transform");
        // TncEngine::Renderer::Submit(m_VertexArray);

        TncEngine::Renderer::EndScene();
    }

    void OnEvent(TncEngine::Event &e) override
    {
        m_CameraController.OnEvent(e);
    }

    bool OnKeyPressedEvent(TncEngine::KeyPressedEvent& event)
    {
        return false;
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");

        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

        ImGui::End();
    }
private:
    TncEngine::Ref<TncEngine::VertexArray> m_VertexArray;
    TncEngine::Ref<TncEngine::VertexArray> m_SquareVertexArray;

    TncEngine::Ref<TncEngine::Texture2D> m_Checkerboard, m_ChernoLogo;

    TncEngine::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sanbox : public TncEngine::Application
{
public:
    Sanbox()
    {
        TncEngine::Renderer2D::Init([]()
        {
            TncEngine::Ref<TncEngine::VertexArray> squareVertexArray = TncEngine::VertexArray::Create();

            float squareVertices[] = {
                -0.5f, -0.5f, -0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, -0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, -0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, -0.0f, 0.0f, 1.0f
            };

            TncEngine::Ref<TncEngine::VertexBuffer> squareVertexBuffer;
            squareVertexBuffer = TncEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

            squareVertexBuffer->SetLayout({
                { TncEngine::ShaderDataType::Float3, "a_Position"},
                { TncEngine::ShaderDataType::Float2, "a_TexCoord"},
            });
            squareVertexArray->AddVertexBuffer(squareVertexBuffer);

            uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
            TncEngine::Ref<TncEngine::IndexBuffer> squareIndexBuffer;
            squareIndexBuffer = TncEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
            squareVertexArray->SetIndexBuffer(squareIndexBuffer);

            auto& shaderLibrary = TncEngine::ShaderLibrary::Get();

            shaderLibrary.Load("FlatColorSquare", "sandbox/assets/shaders/FlatColorSquare.glsl");
            shaderLibrary.Load("Texture", "sandbox/assets/shaders/Texture.glsl");
            shaderLibrary.Load("TextureWithEditableColor" ,"sandbox/assets/shaders/TextureWithEditableColor.glsl");

            return squareVertexArray;
        });

        // PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());

    }

    ~Sanbox()
    {
    }
};

TncEngine::Application *TncEngine::CreateApplication()
{
    return new Sanbox();
}