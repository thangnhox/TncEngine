#pragma once

// For use by TncEngine Applications
#include "TncEngine/core/Application.hpp"
#include "TncEngine/Layers/Layer.hpp"
#include "TncEngine/core/Log.hpp"

#include "TncEngine/Utils/Timestep.hpp"

#include "TncEngine/Input/Input.hpp"
#include "TncEngine/Input/KeyCodes.hpp"
#include "TncEngine/Input/MouseButtonCodes.hpp"

#include "TncEngine/Layers/ImGuiLayer.hpp"
#include "TncEngine/Renderer/OrthographicCameraController.hpp"

// ------   Renderer   -------------
#include "TncEngine/Renderer/Renderer.hpp"
#include "TncEngine/Renderer/RenderCommand.hpp"

#include "TncEngine/Renderer/Buffer.hpp"
#include "TncEngine/Renderer/Shader.hpp"
#include "TncEngine/Renderer/Texture.hpp"
#include "TncEngine/Renderer/VertexArray.hpp"

//---------  DEBUG  ----------------
// Still usable event without define TNC_PROFILE
// But all the macros will be disable
#include "TncEngine/Utils/Instrumentor.hpp"

// ------ Entry Point --------------
// This will be disable by default
// To enable, #define _MAIN_PROGRAM_ in cpp file where you think should place main function
#include "TncEngine/core/EntryPoint.hpp"
// ---------------------------------

