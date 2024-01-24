#pragma once

#include <TncEngine/Layers/Layer.hpp>

#include <TncEngine/Events/ApplicationEvent.hpp>
#include <TncEngine/Events/KeyEvent.hpp>
#include <TncEngine/Events/MouseEvent.hpp>

namespace TncEngine {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;

        void Being();
        void End();
    private:
        float m_Time = 0.0f;
    };

}