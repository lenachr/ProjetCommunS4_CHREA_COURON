#pragma once
#include <glm/glm.hpp>
#include "glm/ext/matrix_transform.hpp"

class TrackballCamera {
private:
    float m_Distance;
    float m_AngleX;
    float m_AngleY;

public:
    // Constructeur initialisant les angles à 0 et la distance à 5
    TrackballCamera()
        : m_Distance(10.0f), m_AngleX(0.0f), m_AngleY(0.0f) {}

    void moveFront(float delta)
    {
        m_Distance = m_Distance + delta;
    }

    void rotateLeft(float degrees)
    {
        m_AngleY = m_AngleY + glm::radians(degrees);
    }

    void rotateUp(float degrees)
    {
        m_AngleX = m_AngleX + glm::radians(degrees);
    }

    glm::mat4 getViewMatrix() const
    {
        float angleX_rad = glm::radians(m_AngleX);
        float angleY_rad = glm::radians(m_AngleY);

        // Calculer les composantes de la direction de la caméra
        glm::vec3 direction(
            cos(angleX_rad) * sin(angleY_rad),
            sin(angleX_rad),
            cos(angleX_rad) * cos(angleY_rad)
        );

        // Calculer la position de la caméra
        glm::vec3 position = m_Distance * direction;

        // Calculer la matrice de vue (View Matrix)
        return glm::lookAt(position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
};
