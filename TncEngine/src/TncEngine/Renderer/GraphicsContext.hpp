#pragma once

#include <TncEngine/core/Core.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TncEngine {

    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}