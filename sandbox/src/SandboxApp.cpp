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

#include <TncEngine/Renderer/OpenGLShader.hpp>

class ExampleLayer : public TncEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
        m_VertexArray.reset(TncEngine::VertexArray::Create());
        m_SquareVertexArray.reset(TncEngine::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, -0.0f,
             0.5f, -0.5f, -0.0f,
             0.5f,  0.5f, -0.0f,
            -0.5f,  0.5f, -0.0f
        };

        TncEngine::Ref<TncEngine::VertexBuffer> vertexBuffer;
        TncEngine::Ref<TncEngine::VertexBuffer> squareVertexBuffer;
        vertexBuffer.reset(TncEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
        squareVertexBuffer.reset(TncEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        vertexBuffer->SetLayout({
            { TncEngine::ShaderDataType::Float3, "a_Position" },
            { TncEngine::ShaderDataType::Float4, "a_Color" }
        });
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        squareVertexBuffer->SetLayout({
            { TncEngine::ShaderDataType::Float3, "a_Position"}
        });
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        TncEngine::Ref<TncEngine::IndexBuffer> indexBuffer;
        indexBuffer.reset(TncEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        TncEngine::Ref<TncEngine::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(TncEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";

        std::string squareVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string squareFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec3 u_Color;

            void main()
            {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_Shader.reset(TncEngine::Shader::Create(vertexSrc, fragmentSrc));
        m_SquareShader.reset(TncEngine::Shader::Create(squareVertexSrc, squareFragmentSrc));
    }

    void OnUpdate(TncEngine::Timestep ts) override
    {
        if (TncEngine::Input::IsKeyPressed(TNC_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        else if (TncEngine::Input::IsKeyPressed(TNC_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * ts;

        if (TncEngine::Input::IsKeyPressed(TNC_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        else if (TncEngine::Input::IsKeyPressed(TNC_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;

        if (TncEngine::Input::IsKeyPressed(TNC_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        else if (TncEngine::Input::IsKeyPressed(TNC_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

        TncEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        TncEngine::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        TncEngine::Renderer::BeginScene();

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        TncEngine::Renderer::Bind(m_SquareShader);
        std::dynamic_pointer_cast<TncEngine::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos = glm::vec3(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                TncEngine::Renderer::Bind(m_SquareShader);
                TncEngine::Renderer::Submit("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
                TncEngine::Renderer::Submit("u_Transform", transform);
                TncEngine::Renderer::Submit(m_SquareVertexArray);
            }
        }

        TncEngine::Renderer::Bind(m_Shader);
        TncEngine::Renderer::Submit("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
        TncEngine::Renderer::Submit("u_Transform");
        TncEngine::Renderer::Submit(m_VertexArray);

        TncEngine::Renderer::EndScene();
    }

    void OnEvent(TncEngine::Event &event) override
    {
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
    TncEngine::Ref<TncEngine::Shader> m_Shader;
    TncEngine::Ref<TncEngine::Shader> m_SquareShader;
    TncEngine::Ref<TncEngine::VertexArray> m_VertexArray;
    TncEngine::Ref<TncEngine::VertexArray> m_SquareVertexArray;

    TncEngine::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 10.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 90.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sanbox : public TncEngine::Application
{
public:
    Sanbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sanbox()
    {
    }
};

TncEngine::Application *TncEngine::CreateApplication()
{
    return new Sanbox();
}