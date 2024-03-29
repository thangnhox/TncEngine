#pragma once

#include <TncEngine/Renderer/Shader.hpp>

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

        void SetFloat4(const std::string& name, const glm::vec4& value) override;
        void SetFloat3(const std::string& name, const glm::vec3& value) override;
        void SetFloat2(const std::string& name, const glm::vec2& value) override;
        void SetFloat(const std::string& name, float value) override;

        void SetInt(const std::string& name, int value) override;

        void SetMat4(const std::string& name, const glm::mat4& value = glm::mat4(1.0f)) override;
        void SetMat3(const std::string& name, const glm::mat3& value = glm::mat3(1.0f)) override;

        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformInt(const std::string& name, int value);

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix = glm::mat4(1.0f));
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix = glm::mat3(1.0f));
    private:
        int GetUniformLocation(const std::string name) const;
    private:
        mutable std::unordered_map<std::string, int> m_UniformLocationCache;
    };

}