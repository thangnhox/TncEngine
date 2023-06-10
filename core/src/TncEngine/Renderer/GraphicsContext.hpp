#pragma once

#include <TncEngine/Core.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TncEngine {

    class TncEngine_API GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}