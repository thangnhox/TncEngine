#pragma once

#include <TncEngine/Renderer/Shader.hpp>

#include <glm/glm.hpp>

namespace TncEngine {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const std::string& sourcePath);
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        void LoadFile(bool compile = false) override;
        void Compile() override;

        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformInt(const std::string& name, int value);

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    private:
        int GetUniformLocation(const std::string name) const;
    private:
        mutable std::unordered_map<std::string, int> m_UniformLocationCache;
    };

}