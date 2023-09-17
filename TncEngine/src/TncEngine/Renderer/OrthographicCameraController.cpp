#include "TncPCH.hpp"
#include "OrthographicCameraController.hpp"

#include <TncEngine/Input/Input.hpp>
#include <TncEngine/Input/KeyCodes.hpp>

namespace TncEngine {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio),
        m_ZoomLevel(1.0f),
        m_OrthographicCamera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
        m_Rotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (TncEngine::Input::IsKeyPressed(TNC_KEY_A))
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        else if (TncEngine::Input::IsKeyPressed(TNC_KEY_D))
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;

        if (TncEngine::Input::IsKeyPressed(TNC_KEY_W))
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        else if (TncEngine::Input::IsKeyPressed(TNC_KEY_S))
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

        m_OrthographicCamera.SetPosition(m_CameraPosition);

        if (m_Rotation)
        {
            if (TncEngine::Input::IsKeyPressed(TNC_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            else if (TncEngine::Input::IsKeyPressed(TNC_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            m_OrthographicCamera.SetRotation(m_CameraRotation);
        }
    }

    void OrthographicCameraController::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(TNC_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(TNC_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
    {
        m_ZoomLevel -= e.GetYOffset();
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_OrthographicCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_OrthographicCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }

}