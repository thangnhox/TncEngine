#pragma once

#include <TncEngine/Core.hpp>

#include <unordered_map>
#include <string>

namespace TncEngine {

    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Compile() = 0;

        // Load Shader source file and compile if needed
        // Can be use as hot reload
        virtual void LoadFile(bool compile = false) = 0;

    protected:
        uint32_t p_RendererID;
        std::string p_SourcePath;
        std::unordered_map<std::string, std::string> p_Sources;
    public:
        static Ref<Shader> Create(const std::string& filepath);
        static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };

}