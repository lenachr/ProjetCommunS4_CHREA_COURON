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

    // Méthode pour détecter les collisions avec les bords du cube
    bool detectCollision() const
    {
        return (m_Position.x < -85.0f || m_Position.x > 85.0f || m_Position.z < -85.0f || m_Position.z > 85.0f);
    }

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

    // Méthode pour gérer les collisions avec les bords du cube
    void handleCollision()
    {
        // Si la caméra dépasse les limites du cube, ajustez sa position
        m_Position.x = glm::clamp(m_Position.x, -85.0f, 85.0f);
        m_Position.z = glm::clamp(m_Position.z, -85.0f, 85.0f);
    }

    // A appeler pour se déplacer vers la droite ou vers la gauche
    void moveLeft(float t)
    {
        m_Position.x += t * m_LeftVector.x;
        m_Position.z += t * m_LeftVector.z;

        if (detectCollision())
        {
            handleCollision();
        }
    }

    // A appeler pour se déplacer vers le haut ou vers le bas
    void moveFront(float t)
    {
        m_Position.x += t * m_FrontVector.x;
        m_Position.z += t * m_FrontVector.z;

        if (detectCollision())
        {
            handleCollision();
        }
    }

    // A appeler pour tourter la caméra vers la gauche ou vers la droite
    void rotateLeft(float degrees)
    {
        // m_Phi += glm::radians(degrees);
        // computeDirectionVectors();
        m_Phi += glm::radians(degrees);
        computeDirectionVectors();
    }

    // A appeler pour tourter la caméra vers le haut ou vers le bas
    void rotateUp(float degrees)
    {
        // m_Theta += glm::radians(degrees);
        // computeDirectionVectors();
        m_Theta += glm::radians(degrees);
        // Limiter l'angle de rotation vertical entre -PI/2 et PI/2 pour éviter le renversement
        m_Theta = glm::clamp(m_Theta, -50 * PI / 2.f, 50 * PI / 2.f);
        computeDirectionVectors();
    }

    glm::mat4 getViewMatrix() const
    {
        glm::vec3 target = m_Position + m_FrontVector; // Déplacez le point de vue légèrement devant la caméra
        // glm::vec3 target = m_Position; // Déplacez le point de vue légèrement devant la caméra
        glm::vec3 up  = m_UpVector;
        glm::vec3 eye = m_Position; // Position de la caméra

        return glm::lookAt(eye, target, up);
    }

    // pour connaitre la position et la direction de la caméra
    glm::vec3 getPosition() const { return m_Position; }
    glm::vec3 getFrontVector() const { return m_FrontVector; }
};
