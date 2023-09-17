#pragma once

#include <TncEngine/Events/Event.hpp>
#include <TncEngine/core/Window.hpp>

#include <TncEngine/Renderer/GraphicsContext.hpp>

namespace TncEngine {

    class OpenGLWindow : public Window
    {
    public:
        OpenGLWindow(const WindowProps& props);
        ~OpenGLWindow() override;

        void OnUpdate();

        inline uint32_t GetWidth() const override { return m_Data.Width; }
        inline uint32_t GetHeight() const override { return m_Data.Height; }
        inline bool IsVSync() const override { return m_Data.VSync; }
        inline bool ShouldClose() const override { return glfwWindowShouldClose(m_Window); }
        inline void* GetNativeWindow() const override { return m_Window; }
        inline bool IsMinimized() const override { return m_Minimized; }
        void SetMinimize(bool enabled) override { m_Minimized = enabled; }

        void SetEventCallback(const EventCallbackFn& callback) override;
        void SetVSync(bool enabled) override;
    private:
        void Init(const WindowProps& props);
        void Shutdown();
    private:
        GLFWwindow* m_Window;
        GraphicsContext* m_Context;

        struct WindowData : public WindowProps
        {
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
        bool m_Minimized = false;
    };

}