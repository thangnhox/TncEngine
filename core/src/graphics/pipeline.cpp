#include "pipeline.hpp"

namespace vulkanEngine { namespace graphics {

    Pipeline::Pipeline()
    {
    }

    Pipeline::Pipeline(const std::string& vertexShader, const std::string& fragmentShader)
        : m_FragmentShader{loadFile(fragmentShader)}, m_VertextShader{loadFile(vertexShader)}
    {
        if (m_FragmentShader.empty() || m_VertextShader.empty())
        {
            std::string log = "file cannot be loaded or empty:";
            if (m_VertextShader.empty())
                log += " " + vertexShader;
            if (m_FragmentShader.empty())
                log += " " + fragmentShader;

            throw std::runtime_error(log);
        }
    }

}}