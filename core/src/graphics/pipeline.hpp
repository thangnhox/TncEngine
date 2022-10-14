#pragma once

#include <string>
#include <stdexcept>

#include "../utils/fileutils.hpp"

namespace vulkanEngine { namespace graphics {

    class Pipeline
    {
        private:
        std::vector<char> m_FragmentShader, m_VertextShader;

        public:
        Pipeline();
        Pipeline(const std::string& vertexShader, const std::string& fragmentShader);

    };

}}