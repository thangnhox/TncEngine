#pragma once

#include <TncEngine/Renderer/OrthographicCamera.hpp>
#include <TncEngine/Utils/Timestep.hpp>

#include <TncEngine/Events/MouseEvent.hpp>
#include <TncEngine/Events/ApplicationEvent.hpp>

namespace TncEngine {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_OrthographicCamera; }
        const OrthographicCamera& GetCamera() const { return m_OrthographicCamera; }

        void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
        float GetZoomLevel() const { return m_ZoomLevel; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel;
        OrthographicCamera m_OrthographicCamera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 10.0f, m_CameraRotationSpeed = 90.0f;
    };

}