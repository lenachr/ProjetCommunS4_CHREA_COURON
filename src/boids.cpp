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

glm::vec4 Boids::position()
{
    glm::vec4 random;
    random = glm::vec4(p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f));
    return random;
}

void Boids::create(p6::Context* ctx, glm::vec4 position)
{
    // Dessin des boids
    glm::vec4 random;
    // random = position();
    ctx->triangle(
        // p6::Point2D{0.1f, 0.1f}, p6::Point2D{0.25f, 0.2f}, p6::Point2D{0.2f, 0.25f}, p6::Center{random.x, random.y}, p6::Rotation{}
        p6::Point2D{0.1f, 0.1f}, p6::Point2D{0.25f, 0.2f}, p6::Point2D{0.2f, 0.25f}, p6::Center{position.x, position.y}, p6::Rotation{}

    );
}