#pragma once

#include "RenderCommand.hpp"

#include <TncEngine/Renderer/OrthographicCamera.hpp>
#include <TncEngine/Renderer/Shader.hpp>

namespace TncEngine {

    class Renderer
    {
    public:
        static void Init();

        static void BeginScene();
        static void EndScene();

        static void Bind(const Ref<Shader>& shader);
        static void Submit(const std::string& name, const glm::mat4& matrix = glm::mat4(1.0f));
        static void Submit(const Ref<VertexArray>& vertexArray);

        static void SetViewPort(uint32_t width, uint32_t height);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        static Ref<Shader> s_Shader;
    };

}