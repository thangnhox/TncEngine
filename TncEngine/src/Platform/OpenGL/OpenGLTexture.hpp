#pragma once

#include <TncEngine/Renderer/Texture.hpp>

namespace TncEngine {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D();

        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

        void SetData(void* data, uint32_t size) override;

        void Bind(uint32_t slot = 0) const override;
        void Unbind(uint32_t slot = 0) const override;

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_Slot, m_TextureID;
        uint32_t m_InternalFormat, m_DataFormat;
        uint32_t m_ColorDepth; // in byte
    };

}