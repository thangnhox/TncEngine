#pragma once

#include <vulkan/vulkan.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "graphics/window.hpp"
#include "graphics/pipeline.hpp"

namespace vulkanEngine
{
    class VulkanEngine
    {

        public:
        VulkanEngine();
        VulkanEngine(const std::string& vertextShader, const std::string& fragmentShader);
        ~VulkanEngine();
        int run();

        protected:
        graphics::Window m_Window;
        graphics::Pipeline m_Pipeline;

    };
}