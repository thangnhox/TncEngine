#pragma once

#include <TncEngine/Events/Event.hpp>
#include <TncEngine/core/Core.hpp>

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

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        
        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual inline uint32_t GetWidth() const = 0;
        virtual inline uint32_t GetHeight() const = 0;
        virtual inline bool IsVSync() const = 0;
        virtual inline bool ShouldClose() const = 0;
        virtual inline void* GetNativeWindow() const = 0;
        virtual inline bool IsMinimized() const = 0;
        virtual void SetMinimize(bool enabled) = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;

        static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
    };

}