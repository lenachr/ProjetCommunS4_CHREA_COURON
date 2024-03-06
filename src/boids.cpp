#include "boids.hpp"
// #include <cstdlib>
// #include <iostream>
// #include "glm/fwd.hpp"
// #include "p6/p6.h"

// constructeur
Boids::Boids()
{
    // Initialisation des variables
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    float     speed    = 0.0f;
}

Boids::Boids(glm::vec2 position, float speed)
    : m_position(position), m_speed(speed)
{
}

// destructeur
Boids::~Boids()
{
}

//
glm::vec4 Boids::position()
{
    glm::vec4 random;
    // random : Position en x, position en y, rotation en x, rotation en y
    random = glm::vec4(p6::random::number(-1.1f, 0.75f), p6::random::number(-1.1f, 0.75f), p6::random::number(-0.9f, 0.9f), p6::random::number(-0.9f, 0.9f));
    return random;
}

void Boids::create(p6::Context* ctx, glm::vec4 position)
{
    // Dessin des boids
    ctx->triangle(
        p6::Point2D{0.1f, 0.1f}, p6::Point2D{0.25f, 0.2f}, p6::Point2D{0.2f, 0.25f}, p6::Center{position.x, position.y}, p6::Rotation{}
    );
}

// Methode qui gère les mouvements
glm::vec4 Boids::speed(glm::vec2* m_speed, glm::vec4 position)
{
    // Si contact mur haut
    if (position.y > 0.75f)
    {
        position.y = -1.1f;
    }
    // Si contact mur bas
    if (position.y < -1.1f)
    {
        position.y = 0.75f;
    }
    // Si contact mur gauche
    if (position.x < -1.1f)
    {
        position.x = 0.75f;
    }
    // Si contact mur droit
    if (position.x > 0.75f)
    {
        position.x = -1.1f;
    }
    // On retourne la nouvelle position
    position.x += m_speed->x;
    position.y += m_speed->y;
    return position;
}
