#include "TncPCH.hpp"
#include "RenderCommand.hpp"

#include <TncEngine/Renderer/OpenGLRendererAPI.hpp>

namespace TncEngine {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
    
}