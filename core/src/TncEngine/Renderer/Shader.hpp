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
        uint32_t m_RendererID;
        std::string m_SourcePath;
        std::unordered_map<std::string, std::string> m_Sources;

    public:
        static Ref<Shader> Create(const std::string& filepath);
        static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    // Shader container
    class ShaderLibrary
    {
    public:
        ShaderLibrary(const ShaderLibrary&) = delete;
        static ShaderLibrary& Get();

    public:
        void Add(const std::string& name ,const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filePath);
        Ref<Shader> Load(const std::string& name, const std::string& filePath);

        Ref<Shader> Get(const std::string& name);
        bool Exists(const std::string& name);

    private:
        ShaderLibrary() {}
        
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };

}