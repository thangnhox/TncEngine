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

        void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexArray; }
        const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
    private:
        uint32_t m_ArrayID;
        std::vector<Ref<VertexBuffer>> m_VertexArray;
        Ref<IndexBuffer> m_IndexBuffer;
    };

}