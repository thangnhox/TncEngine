#pragma once

#include "RenderCommand.hpp"

#include <TncEngine/Renderer/OrthographicCamera.hpp>
#include <TncEngine/Renderer/Shader.hpp>

#include <TncEngine/Renderer/Texture.hpp>

namespace TncEngine {

    class Renderer
    {
    public:
        static void Init();

        static void BeginScene();
        static void EndScene();

        static void BindShader(const Ref<Shader>& shader);
        static void UnbindShader();
        static void BindTexture(const Ref<Texture>& texture, uint32_t slot = 0);
        static void UnbindTexture(uint32_t slot = 0);
        static void UnbindTexture(const Ref<Texture>& texture);

        static void Submit(const Ref<VertexArray>& vertexArray);
        static void Submit(const std::string& name, const glm::mat4& value = glm::mat4(1.0f));
        static void Submit(const std::string& name, const glm::vec4& value);
        static void Submit(const std::string& name, float value);
        static void Submit(const std::string& name, int value);
        static void Submit(const std::function<void(const Ref<Shader>&)>& func);

        static void SetViewPort(uint32_t width, uint32_t height);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        inline static void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }
    };

}