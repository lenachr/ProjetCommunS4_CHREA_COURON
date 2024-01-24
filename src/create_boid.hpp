#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "p6/p6.h"

// classe avec position et vitesse pour chaque boid
class Boids()
{
private:
    // Attribut
    glm::vec2 m_position;
    float     m_speed;

public:
    // fonctions
    void speed();
    void position();
}