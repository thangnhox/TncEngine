#pragma once

#include <glm/glm.hpp>

namespace TncEngine {

    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; ReCalculateViewPatrix(); }

        float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation) { m_Rotation = rotation; ReCalculateViewPatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    private:
        void ReCalculateViewPatrix();
    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix; // this is directX name it should be m_ProjectionViewMatrix

        glm::vec3 m_Position;
        float m_Rotation = 0.0f;
    };

}