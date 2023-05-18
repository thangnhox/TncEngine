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

        inline Window& GetWindow() { return *m_Window; }
        
        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowClosedEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };

    // TOBE: define in client
    Application* CreateApplication();

}