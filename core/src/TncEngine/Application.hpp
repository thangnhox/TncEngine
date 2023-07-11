#pragma once

#include <TncEngine/Core.hpp>

#include <TncEngine/Window.hpp>
#include <TncEngine/Layers/LayerStack.hpp>
#include <TncEngine/Events/Event.hpp>
#include <TncEngine/Events/ApplicationEvent.hpp>

#include <TncEngine/Layers/ImGuiLayer.hpp>

#include <TncEngine/Renderer/Shader.hpp>
#include <TncEngine/Renderer/Buffer.hpp>

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
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running;
        LayerStack m_LayerStack;

        uint32_t m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    private:
        static Application* s_Instance;
    };

    // TOBE: define in client
    Application* CreateApplication();

}