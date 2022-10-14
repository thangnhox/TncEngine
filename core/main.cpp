#include <iostream>
#include "src/VulkanEngine.hpp"

int main()
{
    using namespace vulkanEngine;

    try
    {
        VulkanEngine app{"src/shaders/simple.vert.spv", "src/shaders/simple.frag.spv"};
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return EXIT_SUCCESS;
}