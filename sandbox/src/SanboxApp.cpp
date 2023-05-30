#include <TncEngine.hpp>

class ExampleLayer : public TncEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {}

    void OnUpdate() override
    {
        if (TncEngine::Input::IsKeyPressed(TNC_KEY_TAB))
            TncEngine_TRACE("Tab key is pressed! (poll)");
    }

    void OnEvent(TncEngine::Event& event) override
    {
        if (event.GetEventType() == TncEngine::EventType::KeyPressed)
        {
            TncEngine::KeyPressedEvent& e = (TncEngine::KeyPressedEvent&)event;
            if (e.GetKeyCode() == TNC_KEY_TAB)
                TncEngine_TRACE("Tab key is pressed! (event)");
            TncEngine_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
};

class Sanbox : public TncEngine::Application
{
public:
    Sanbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new TncEngine::ImGuiLayer());
    }

    ~Sanbox()
    {
    }
};

TncEngine::Application* TncEngine::CreateApplication()
{
    return new Sanbox();
}