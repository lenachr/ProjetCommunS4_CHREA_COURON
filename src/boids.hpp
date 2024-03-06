#pragma once

#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"

// #define DOCTEST_CONFIG_IMPLEMENT
// #include "doctest/doctest.h"
#include "p6/p6.h"

// classe avec position et vitesse pour chaque boid
class Boids {
private:
    // Attribut
    glm::vec2 m_position;
    glm::vec2 m_speed;

public:
    // constructeurs
    Boids();
    Boids(glm::vec2 position, float speed);
    // destructeur
    ~Boids();

    // fonctions
    glm::vec4 position();
    void      create(p6::Context* ctx, glm::vec4 position);
    glm::vec4 speed(glm::vec2* m_speed, glm::vec4 position);
};