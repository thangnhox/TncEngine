#include "TncPCH.hpp"
#include "OpenGLTexture.hpp"

#include <glad/glad.h>

#include <stb_image.hpp>

namespace TncEngine {

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height), m_ColorDepth(4)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
        glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string &path)
        : m_Path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        ASSERT_CORE(data, "Failed to load image");
        m_Width = width;
        m_Height = height;
        m_ColorDepth = channels;

        switch (channels)
        {
        case 3:
        {
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
        } break;

        case 4:
        {
            m_InternalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
        } break;
        
        default:
            break;
        }

        ASSERT_CORE(m_InternalFormat & m_DataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
        glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void OpenGLTexture2D::SetData(void *data, uint32_t size)
    {
        uint32_t textureSize = m_Width * m_Height * m_ColorDepth;
        ASSERT_CORE(textureSize == size, "Failed to validate texture data size!");
        glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_TextureID);
    }

    void OpenGLTexture2D::Unbind(uint32_t slot) const
    {
        glBindTextureUnit(slot, 0);
    }

}