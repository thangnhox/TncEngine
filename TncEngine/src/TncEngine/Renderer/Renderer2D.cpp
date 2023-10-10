#include "TncPCH.hpp"
#include "Renderer2D.hpp"

#include <TncEngine/Renderer/Renderer.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace TncEngine {

    struct Renderer2DStorage
    {
        Ref<VertexArray> d_VertexArray;
        std::vector<Ref<Shader>> d_Shaders;
        Ref<Texture> d_DefaultTexture;
    };

    static Renderer2DStorage* s_Data = nullptr;

    // Custom init
    // Allow user to init VertexArray to store inside Renderer2D
    void Renderer2D::Init(const std::function<Ref<VertexArray>()> &func)
    {
        if (s_Data)
        {
            TncEngine_CORE_ERROR("Render2d Already inited!");
            return;
        }
        s_Data = new Renderer2DStorage();
        s_Data->d_Shaders.reserve(4);
        s_Data->d_DefaultTexture = Texture2D::Create(1, 1);
        uint32_t white = 0xffffffff;
        s_Data->d_DefaultTexture->SetData(&white, sizeof(uint32_t));
        s_Data->d_VertexArray = func();
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::EnableShader(const Ref<Shader> &shader)
    {
        s_Data->d_Shaders.push_back(shader);
    }

    // begin 2d scene
    // shader already bind so feel free to upload anything to it in lambda
    void Renderer2D::BeginScene(const Ref<Shader> &shader, const std::function<void(const Ref<Shader> &)> &prepare)
    {
        EnableShader(shader);
        Renderer::BindShader(shader);
        Renderer::Submit(prepare);
    }

    void Renderer2D::BeginScene(const Ref<Shader> &shader, const OrthographicCamera &camera)
    {
        EnableShader(shader);
        Renderer::BindShader(shader);
        Renderer::Submit("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {
        for (auto& shader : s_Data->d_Shaders)
        {
            Renderer::BindShader(shader);
            Renderer::Submit("u_ViewProjection", camera.GetViewProjectionMatrix());
        }
    }

    void Renderer2D::EndScene()
    {
        s_Data->d_Shaders.clear();
        Renderer::UnbindShader();
    }

    void Renderer2D::Draw()
    {
        Renderer::Submit(s_Data->d_VertexArray);
    }

    void Renderer2D::Draw(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, int shaderIndex)
    {
        Draw({position.x, position.y, 0.0f}, size, color, shaderIndex);
    }

    void Renderer2D::Draw(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, int shaderIndex)
    {
        if (s_Data->d_Shaders.empty())
        {
            TncEngine_CORE_FATAL("No Shader Currently enable!");
            return;
        }
        Renderer::BindShader(s_Data->d_Shaders[shaderIndex]);

        Renderer::Submit("u_Color", color);
        Renderer::Submit("u_Scale", 1.0f);
        Renderer::BindTexture(s_Data->d_DefaultTexture);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        Renderer::Submit("u_Transform", transform);

        Renderer::Submit(s_Data->d_VertexArray);
    }

    void Renderer2D::Draw(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, int shaderIndex)
    {
        Draw({ position.x, position.y, 0.0f }, size, texture, shaderIndex);
    }

    void Renderer2D::Draw(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, int shaderIndex)
    {
        if (s_Data->d_Shaders.empty())
        {
            TncEngine_CORE_FATAL("No Shader Currently enable!");
            return;
        }
        Renderer::BindShader(s_Data->d_Shaders[shaderIndex]);

        Renderer::Submit("u_Scale", 1.0f);
        Renderer::Submit("u_Color", glm::vec4(1.0f));

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        Renderer::Submit("u_Transform", transform);

        Renderer::BindTexture(texture);
        
        Renderer::Submit(s_Data->d_VertexArray);
    }

}