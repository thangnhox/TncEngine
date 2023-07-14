#pragma once

#include <TncEngine/Renderer/VertexArray.hpp>

namespace TncEngine {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexArray; }
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
    private:
        uint32_t m_ArrayID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexArray;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };

}