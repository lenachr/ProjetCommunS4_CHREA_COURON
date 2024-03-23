#pragma once
#include "glm/glm.hpp"
#include "p6/p6.h"

class Boid {
public:
    Boid(glm::vec2 position, glm::vec2 speed)
        : position{position}, speed{speed}
    {}

    void draw(p6::Context* ctx);
    void update(const std::vector<Boid>& allBoid, float alignement_coeff, float cohesion_coeff, float separation_coeff);
    ~Boid();

private:
    void  apply_speed();
    void  separation(const std::vector<Boid>& allBoid, float separationDistance, float separationFactor);
    void  alignement(const std::vector<Boid>& allBoid, double alignmentDistance);
    float distance(const Boid& boid1, const Boid& boid2);
    void  cohesion(const std::vector<Boid>& allBoids, double cohesionDistance, double cohesionFactor);

private:
    glm::vec2 position;
    glm::vec2 speed;
};