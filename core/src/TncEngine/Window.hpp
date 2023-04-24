#pragma once

#include <TncPCH.hpp>
#include <TncEngine/Events/Event.hpp>

#include <GLFW/glfw3.h>

namespace TncEngine {

    struct WindowProps
    {
        std::string Title;
        uint32_t Width, Height;

        WindowProps(const std::string& title = "TncEngine", uint32_t width = 1280, uint32_t height = 720)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    class TncEngine_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        ~Window();

        void OnUpdate();

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFn& callback);
        void SetVSync(bool enabled);
        bool IsVSync() const { return m_Data.VSync; }

        static Window* Create(const WindowProps& props = WindowProps());
    private:
        Window(const WindowProps& props);
        void Init(const WindowProps& props);
        void Shutdown();
    private:
        GLFWwindow* m_Window;

        struct WindowData : public WindowProps
        {
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

}