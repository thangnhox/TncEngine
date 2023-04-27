#pragma once

#include <TncEngine/Core.hpp>

#include <TncEngine/Window.hpp>
#include <TncEngine/Layers/LayerStack.hpp>
#include <TncEngine/Events/Event.hpp>
#include <TncEngine/Events/ApplicationEvent.hpp>


namespace TncEngine {

    class TncEngine_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClose(WindowClosedEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running;
        LayerStack m_LayerStack;
    };

    // TOBE: define in client
    Application* CreateApplication();

}