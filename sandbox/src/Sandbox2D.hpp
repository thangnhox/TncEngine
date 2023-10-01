#pragma once

#include <TncEngine.hpp>

class Sandbox2D : public TncEngine::Layer
{
public:
    Sandbox2D();

    void OnUpdate(TncEngine::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(TncEngine::Event& e) override;
    
    void OnAttach() override;
    void OnDetach() override;

private:
    TncEngine::OrthographicCameraController m_CameraController;
    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

    //Temp
    TncEngine::Ref<TncEngine::VertexArray> m_SquareVertexArray;

};