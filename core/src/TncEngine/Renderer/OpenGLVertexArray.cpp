#include "TncPCH.hpp"
#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

namespace TncEngine {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:         return GL_FLOAT;
            case ShaderDataType::Float2:        return GL_FLOAT;
            case ShaderDataType::Float3:        return GL_FLOAT;
            case ShaderDataType::Float4:        return GL_FLOAT;
            case ShaderDataType::Mat3:          return GL_FLOAT;
            case ShaderDataType::Mat4:          return GL_FLOAT;
            case ShaderDataType::Int:           return GL_INT;
            case ShaderDataType::Int2:          return GL_INT;
            case ShaderDataType::Int3:          return GL_INT;
            case ShaderDataType::Int4:          return GL_INT;
            case ShaderDataType::Bool:          return GL_BOOL;
            case ShaderDataType::None:          break;
        }

        ASSERT_CORE(false, "Unsupported ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_ArrayID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_ArrayID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_ArrayID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
    {
        ASSERT_CORE(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_ArrayID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetCompomentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset
            );
            index++;
        }

        m_VertexArray.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
    {
        glBindVertexArray(m_ArrayID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

}