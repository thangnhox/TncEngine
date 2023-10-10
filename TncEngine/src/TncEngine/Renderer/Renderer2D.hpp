#pragma once

#include <TncEngine/Renderer/VertexArray.hpp>
#include <TncEngine/Renderer/Shader.hpp>

#include <TncEngine/Renderer/OrthographicCamera.hpp>
#include <TncEngine/Renderer/Texture.hpp>

namespace TncEngine {

    class Renderer2D
    {
    public:
        static void Init(const std::function<Ref<VertexArray>()>& func);
        static void Shutdown();

        static void EnableShader(const Ref<Shader>& shader);

        static void BeginScene(const Ref<Shader>& shader, const std::function<void(const Ref<Shader>&)>& prepare);
        static void BeginScene(const Ref<Shader>& shader, const OrthographicCamera& camera);
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void Draw();
        static void Draw(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, int shaderIndex = 0);
        static void Draw(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int shaderIndex = 0);
        static void Draw(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, int shaderIndex = 0);
        static void Draw(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, int shaderIndex = 0);
    };

}