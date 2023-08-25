#pragma once

#include "RenderCommand.hpp"

#include <TncEngine/Renderer/OrthographicCamera.hpp>
#include <TncEngine/Renderer/Shader.hpp>

namespace TncEngine {

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Bind(const std::shared_ptr<Shader>& shader);
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        static void Submit(const std::string& name, const glm::mat4& matrix);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        static std::shared_ptr<Shader> s_Shader;
    };

}