#include <TncEngine.hpp>

class ExampleLayer : public TncEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {}

    void OnUpdate() override
    {
        TncEngine_INFO("ExampleLayer::Update");
    }

    void OnEvent(TncEngine::Event& event) override
    {
        TncEngine_TRACE("{0}", event);
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