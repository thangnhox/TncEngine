#include <TncEngine.hpp>

// #include <glm/vec3.hpp>                 // glm::vec3
// #include <glm/vec4.hpp>                 // glm::vec4
// #include <glm/mat4x4.hpp>               // glm::mat4
// #include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
// glm::mat4 camera(float Translate, glm::vec2 const &Rotate)
// {
//     glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
//     glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//     View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//     View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//     glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//     return Projection * View * Model;
// }

#include <imgui.h>

class ExampleLayer : public TncEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        if (TncEngine::Input::IsKeyPressed(TNC_KEY_TAB))
            TncEngine_TRACE("Tab key is pressed! (poll)");
    }

    void OnEvent(TncEngine::Event &event) override
    {
        if (event.GetEventType() == TncEngine::EventType::KeyPressed)
        {
            TncEngine::KeyPressedEvent &e = (TncEngine::KeyPressedEvent &)event;
            if (e.GetKeyCode() == TNC_KEY_TAB)
                TncEngine_TRACE("Tab key is pressed! (event)");
            TncEngine_TRACE("{0}", (char)e.GetKeyCode());
        }
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }
};

class Sanbox : public TncEngine::Application
{
public:
    Sanbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sanbox()
    {
    }
};

TncEngine::Application *TncEngine::CreateApplication()
{
    return new Sanbox();
}