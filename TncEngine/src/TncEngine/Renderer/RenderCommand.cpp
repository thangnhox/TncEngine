#include "TncPCH.hpp"
#include "RenderCommand.hpp"

#include <Platform/OpenGL/OpenGLRendererAPI.hpp>

namespace TncEngine {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
    
}