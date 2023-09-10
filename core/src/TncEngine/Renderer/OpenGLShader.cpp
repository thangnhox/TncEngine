#include "TncPCH.hpp"
#include "OpenGLShader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <TncEngine/Utils/StringUtils.hpp>

namespace TncEngine {

    GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vert")
            return GL_VERTEX_SHADER;
        if (type == "tesc")
            return GL_TESS_CONTROL_SHADER;
        if (type == "tese")
            return GL_TESS_EVALUATION_SHADER;
        if (type == "geom")
            return GL_GEOMETRY_SHADER;
        if (type == "frag")
            return GL_FRAGMENT_SHADER;
        if (type == "comp")
            return GL_COMPUTE_SHADER;

        TncEngine_CORE_FATAL("Invalid shader type '{0}'", type);
        return GL_NONE;
    }

    OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        m_RendererID = 0;
        m_SourcePath.clear();
        m_Sources["vert"] = vertexSrc;
        m_Sources["frag"] = fragmentSrc;
        Compile();
    }

    OpenGLShader::OpenGLShader(const std::string &sourcePath)
    {
        m_RendererID = 0;
        m_SourcePath = sourcePath;
        LoadFile();
        Compile();
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::LoadFile(bool compile)
    {
        if (m_SourcePath.empty())
        {
            ASSERT_CORE(false, "This Shader instance [{0}] doesn't init with file path", fmt::ptr(this));
            return;
        }
        std::string source = StringUtils::LoadFile(m_SourcePath);
        if (source.empty()) return;
        m_Sources = StringUtils::SplitString("#type", source);

        if (compile) Compile();
    }

    void OpenGLShader::Compile()
    {
        if (m_Sources.empty())
        {
            TncEngine_CORE_ERROR("This Shader instance [{0}] has no source!", fmt::ptr(this));
            return;
        }

        // I personally like to keep this dynamic in case other shader type such as tessellation and geometry shader
        // It's just few bytes anyway :)
        std::vector<GLuint> shaderIDs;
        shaderIDs.reserve(m_Sources.size());

        // Get a program object.
        GLuint program = glCreateProgram();

        for (auto& kv : m_Sources)
        {
            GLenum type = ShaderTypeFromString(kv.first);

            if (!type)
            {
                TncEngine_CORE_ERROR("Invalid shader type '{0}'", kv.first);
                continue;
            }

            GLuint shader = glCreateShader(type);
            shaderIDs.push_back(shader);

            const GLchar* source = kv.second.c_str();
            glShaderSource(shader, 1, &source, 0);

            // compile vertex shader
            glCompileShader(shader);

            int isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                
                // We don't need the shader anymore.
                for (auto id : shaderIDs)
                    glDeleteShader(id);

                TncEngine_CORE_ERROR("{0}", infoLog.data());
                ASSERT_CORE(false, kv.first + " shader compilation failure");
                return;
            }
            glAttachShader(program, shader);
        }

        if (shaderIDs.empty())
        {
            TncEngine_CORE_ERROR("This Shader instance [{0}] has no valid source type found!", fmt::ptr(this));
            return;
        }

        // Link our program
        glLinkProgram(program);

        // Check linking
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            for (auto id : shaderIDs)
                glDeleteShader(id);

            TncEngine_CORE_ERROR("{0}", infoLog.data());
            ASSERT_CORE(false, "Shader link failure!");
            return;
        }

        // Always detach shaders after a successful link.
        for (auto id : shaderIDs)
            glDetachShader(program, id);

        // Delete Existing program for this instance
        if (m_RendererID)
        {
            glDeleteProgram(m_RendererID);
        }
        m_RendererID = program;
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 &matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    int OpenGLShader::GetUniformLocation(const std::string name) const
    {
        if (m_UniformLocationCache.find(name) == m_UniformLocationCache.end())
            m_UniformLocationCache[name] = glGetUniformLocation(m_RendererID, name.c_str());
        return m_UniformLocationCache[name];
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &value)
    {
        glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &value)
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &value)
    {
        glUniform2f(GetUniformLocation(name), value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, float value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

}