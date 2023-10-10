#pragma once

#include <TncEngine/core/Core.hpp>

#include <TncEngine/core/Window.hpp>
#include <TncEngine/Layers/LayerStack.hpp>
#include <TncEngine/Events/Event.hpp>
#include <TncEngine/Events/ApplicationEvent.hpp>

#include <TncEngine/Layers/ImGuiLayer.hpp>

namespace TncEngine {

    class Application
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
        bool OnWindowResizedEvent(WindowResizeEvent& e);
    protected:
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
        static Application* s_Instance;
    };

    // TOBE: define in client
    Application* CreateApplication();

}