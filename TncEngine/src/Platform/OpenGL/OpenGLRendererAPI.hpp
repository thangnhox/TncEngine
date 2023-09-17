#pragma once

#include <TncEngine/Renderer/RendererAPI.hpp>

namespace TncEngine {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;

        void SetClearColor(const glm::vec4& color) override;
        void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void Clear() override;

        void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };

}