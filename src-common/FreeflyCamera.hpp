#pragma once
#include <cmath>
#include <cstdio>
#include <glm/glm.hpp>
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

static constexpr float TAU = 6.2831853f;
static constexpr float PI  = TAU / 2.f;

class FreeflyCamera {
private:
    glm::vec3 m_Position;
    float     m_Phi;
    float     m_Theta;
    glm::vec3 m_FrontVector; // F
    glm::vec3 m_LeftVector;  // L
    glm::vec3 m_UpVector;    // U

    void computeDirectionVectors()
    {
        m_FrontVector = glm::vec3(
            cos(glm::radians(m_Theta)) * sin(glm::radians(m_Phi)),
            sin(glm::radians(m_Theta)),
            // 0,
            cos(glm::radians(m_Theta)) * cos(glm::radians(m_Phi))
        );

        m_LeftVector = glm::vec3(
            sin(glm::radians(m_Phi) + PI / 2),
            0,
            cos(glm::radians(m_Phi) + PI / 2)
        );

        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }

public:
    FreeflyCamera()
        : m_Position(0.f, 6.f, 0.0f), m_Phi(PI), m_Theta(0.f)
    {
        computeDirectionVectors();
    }

    // A appeler pour se déplacer vers la droite ou vers la gauche
    void moveLeft(float t)
    {
        // m_Position += t * m_LeftVector;
        m_Position.x += t * m_LeftVector.x;
        m_Position.z += t * m_LeftVector.z;
    }

    // A appeler pour se déplacer vers le haut ou vers le bas
    void moveFront(float t)
    {
        // m_Position += t * m_FrontVector;
        m_Position.x += t * m_FrontVector.x;
        m_Position.z += t * m_FrontVector.z;
    }

    // A appeler pour tourter la caméra vers la gauche ou vers la droite
    void rotateLeft(float degrees)
    {
        m_Phi += glm::radians(degrees);
        computeDirectionVectors();
    }

    // A appeler pour tourter la caméra vers le haut ou vers le bas
    void rotateUp(float degrees)
    {
        m_Theta += glm::radians(degrees);
        computeDirectionVectors();
    }

    glm::mat4 getViewMatrix() const
    {
        glm::vec3 target = m_Position + m_FrontVector; // Déplacez le point de vue légèrement devant la caméra
        glm::vec3 up     = m_UpVector;
        glm::vec3 eye    = m_Position; // Position de la caméra

        return glm::lookAt(eye, target, up);
    }

    // pour connaitre la position et la direction de la caméra
    glm::vec3 getPosition() const { return m_Position; }
    glm::vec3 getFrontVector() const { return m_FrontVector; }
};
